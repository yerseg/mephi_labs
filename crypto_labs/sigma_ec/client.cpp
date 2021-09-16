#include "client.h"

#include <eccrypto.h>
#include <osrng.h>
#include <oids.h>
#include <modes.h>

using namespace CryptoPP;

Client::Client(const std::string& clientName)
    : m_clientName(clientName)
{
    AutoSeededRandomPool prng;

    // ECDSA
    ECDSA<ECP, SHA256>::PrivateKey ecdsaSK;
    ECDSA<ECP, SHA256>::PublicKey ecdsaPK;

    ecdsaSK.Initialize(prng, ASN1::secp256k1());
    ecdsaSK.Save(m_ecdsaSK);
    ecdsaSK.MakePublicKey(ecdsaPK);
    ecdsaPK.Save(m_ecdsaPK);

    //ECDH
    ECDH<ECP>::Domain ecdh(ASN1::secp256k1());

    m_dhSK = SecByteBlock(ecdh.PrivateKeyLength());
    m_dhPK = SecByteBlock(ecdh.PublicKeyLength());
    ecdh.GenerateKeyPair(prng, m_dhSK, m_dhPK);

    m_r = SecByteBlock(AES::BLOCKSIZE);
    prng.GenerateBlock(m_r.BytePtr(), AES::BLOCKSIZE);
}

void Client::SetSignatureFriendKey(const std::string& name, const ByteQueue& key)
{
    m_friendKeys[name].first = key;
}

void Client::SetFriendDataForSharedSecret(const std::string& name, const std::pair<SecByteBlock, SecByteBlock>& keys)
{
    m_friendKeys[name].second.first = keys.first;
    m_friendKeys[name].second.second = keys.second;
    ComputeSharedKeys(name);
}

std::string Client::GetName() const
{
    return m_clientName;
}

ByteQueue Client::GetSignaturePublicKey() const
{
    return m_ecdsaPK;
}

std::pair<SecByteBlock, SecByteBlock> Client::GetDataForSharedSecret(Client& receiver)
{
    SetOrder(receiver.GetName(), false);
    receiver.SetOrder(m_clientName, true);
    return {m_dhPK, m_r};
}

std::vector<CryptoPP::SecByteBlock> Client::GetSignatureAndData(const std::string& name)
{
    SecByteBlock toSign;
    if (m_isFirstForCompute[name])
    {
        toSign = m_friendKeys[name].second.first + m_dhPK;
    }
    else
    {
        toSign = m_dhPK + m_friendKeys[name].second.first;
    }

    AutoSeededRandomPool prng;
    ECDSA<ECP, SHA256>::Signer ecdsaSigner(m_ecdsaSK);

    SecByteBlock signature(ecdsaSigner.SignatureLength());
    ecdsaSigner.SignMessage(prng, toSign, toSign.SizeInBytes(), signature.BytePtr());

    HMAC<SHA256> hmac;
    SecByteBlock mac(hmac.DigestSize());
    hmac.SetKey(m_sharedM.BytePtr(), m_sharedM.SizeInBytes());
    hmac.Update((byte*)(m_clientName.c_str()), m_clientName.size());
    hmac.Final(mac.BytePtr());

    return {
        m_dhPK, m_r, SecByteBlock((byte*)(m_clientName.c_str()), m_clientName.size()),
        signature, mac
    };
}

void Client::Connect(const std::vector<CryptoPP::SecByteBlock>& data)
{
    std::string name((char*)(data[2].BytePtr()), data[2].SizeInBytes());

    m_friendKeys[name].second.first = data[0];
    m_friendKeys[name].second.second = data[1];

    SecByteBlock mac = data[4];
    HMAC<SHA256> hmac;

    hmac.SetKey(m_sharedM.BytePtr(), m_sharedM.size());
    hmac.Update(data[2].BytePtr(), data[2].SizeInBytes());
    if (!hmac.Verify(mac.BytePtr()))
    {
        std::ostringstream stream;
        stream << "Invalid MAC from " << name;
        throw std::runtime_error(stream.str());
    }

    SecByteBlock signature = data[3];
    SecByteBlock message;

    if (m_isFirstForCompute[name])
    {
        message = m_friendKeys[name].second.first + m_dhPK;
    }
    else
    {
        message = m_dhPK + m_friendKeys[name].second.first;
    }

    ECDSA<ECP, SHA256>::PublicKey publicKey;
    publicKey.Load(m_friendKeys[name].first);

    ECDSA<ECP, SHA256>::Verifier ecdsaVerifier(publicKey);
    if (!ecdsaVerifier.VerifyMessage(message.BytePtr(), message.SizeInBytes(), signature.BytePtr(),
                                     signature.SizeInBytes()))
    {
        std::ostringstream stream;
        stream << "Invalid signature from " << name;
        throw std::runtime_error(stream.str());
    }
}

void Client::ComputeSharedKeys(const std::string& name)
{
    if (!m_friendKeys.contains(name))
    {
        std::ostringstream stream;
        stream << m_clientName << "don't know " << name;
        throw std::runtime_error(stream.str());
    }

    SecByteBlock dhKey, r;
    dhKey = m_friendKeys[name].second.first;
    r = m_friendKeys[name].second.second;

    SecByteBlock key;
    if (m_isFirstForCompute[name])
    {
        key = r + m_r;
    }
    else
    {
        key = m_r + r;
    }

    AutoSeededRandomPool prng;
    ECDH<ECP>::Domain ecdh(ASN1::secp256k1());

    SecByteBlock sharedKey(ecdh.AgreedValueLength());

    if (!ecdh.Agree(sharedKey.BytePtr(), m_dhSK.BytePtr(), m_friendKeys[name].second.first))
    {
        std::ostringstream stream;
        stream << "Failed to reach shared secret with " << name;
        throw std::runtime_error(stream.str());
    }

    HMAC<SHA256> hmac;
    hmac.SetKey(key.BytePtr(), key.SizeInBytes());
    hmac.Update(sharedKey.BytePtr(), sharedKey.SizeInBytes());

    SecByteBlock buffer(hmac.DigestSize());
    hmac.Final(buffer.BytePtr());

    m_sharedE = SecByteBlock(buffer.BytePtr(), buffer.SizeInBytes() / 2);
    m_sharedM = SecByteBlock(buffer.BytePtr() + buffer.SizeInBytes() / 2, buffer.SizeInBytes() / 2);
}

SecByteBlock Client::SendMessage(const std::string& message)
{
    AutoSeededRandomPool prng;
    SecByteBlock iv(AES::BLOCKSIZE);
    prng.GenerateBlock(iv.BytePtr(), iv.SizeInBytes());

    HMAC<SHA256> hmac;
    SecByteBlock tag(hmac.DigestSize());
    hmac.SetKey(m_sharedM.BytePtr(), m_sharedM.SizeInBytes());
    hmac.Update(iv.BytePtr(), iv.SizeInBytes());

    SecByteBlock output(message.size());
    CTR_Mode<AES>::Encryption aesEncryption;
    aesEncryption.SetKeyWithIV(m_sharedE.BytePtr(), m_sharedE.SizeInBytes(), iv.BytePtr(), iv.SizeInBytes());
    aesEncryption.ProcessData(output.BytePtr(), (byte*)message.c_str(), message.size());

    hmac.Update(output.BytePtr(), output.SizeInBytes());
    hmac.Final(tag.BytePtr());

    output += tag;
    iv += output;

    return iv;
}

std::string Client::ReceiveMessage(const SecByteBlock& message)
{
    HMAC<SHA256> hmac;
    const auto dataLength = message.SizeInBytes() - hmac.DigestSize();
    SecByteBlock tag(message.BytePtr() + dataLength, hmac.DigestSize());
    SecByteBlock data(message.BytePtr(), dataLength);

    hmac.SetKey(m_sharedM.BytePtr(), m_sharedM.SizeInBytes());
    hmac.Update(data.BytePtr(), data.SizeInBytes());
    if (!hmac.Verify(tag.BytePtr()))
        throw std::runtime_error("Invalid MAC tag!");

    SecByteBlock iv(data.BytePtr(), AES::BLOCKSIZE);
    SecByteBlock cipher(data.BytePtr() + AES::BLOCKSIZE, data.SizeInBytes() - AES::BLOCKSIZE);

    SecByteBlock output(cipher.size());
    CTR_Mode<AES>::Decryption aesDecryption;
    aesDecryption.SetKeyWithIV(m_sharedE.BytePtr(), m_sharedE.SizeInBytes(), iv.BytePtr(), iv.SizeInBytes());
    aesDecryption.ProcessData(output.BytePtr(), cipher.BytePtr(), cipher.SizeInBytes());

    return std::string((char*)output.BytePtr(), output.SizeInBytes());
}

void Client::SetOrder(const std::string& name, bool status)
{
    if (!m_isFirstForCompute.contains(name))
        m_isFirstForCompute[name] = status;
}
