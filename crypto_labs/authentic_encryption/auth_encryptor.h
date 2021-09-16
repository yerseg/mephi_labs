#ifndef __AUTH_ENCRYPTOR__
#define __AUTH_ENCRYPTOR__

#include "../hash/bytearray.h"
#include "../mac/helpers.h"
#include "../mac/hmac.h"

namespace crypto
{
namespace auth
{
namespace mode
{
enum Mode
{
    Encrypt,
    Decrypt
};
}

class AuthenticEncryptor
{
public:
    explicit AuthenticEncryptor(mode::Mode mode);

    void SetKey(ByteArray key);
    void SetMacKey(ByteArray key);
    ByteArray ProcessData(ByteArray data);
    void AddBlock(ByteArray block);

private:

    ByteArray m_key;
    ByteArray m_data;
    ByteArray m_counter;
    ByteArray m_mac;
    mode::Mode m_mode;
    mac::HmacProvider m_hmacObj;

};

inline AuthenticEncryptor::AuthenticEncryptor(mode::Mode mode) : m_mode(mode)
{
}

inline void AuthenticEncryptor::SetKey(ByteArray key)
{
    m_data.Clear();
    m_key.Clear();

    m_key = key;
}

inline void AuthenticEncryptor::SetMacKey(ByteArray key)
{
    m_hmacObj.SetKey(key);
}

inline void AuthenticEncryptor::AddBlock(ByteArray block)
{
    const ByteArray newBlock = helpers::AesBlockEncrypt(m_key, m_counter, helpers::padding_type::PKCS7);
    helpers::IncrementByteArray(m_counter);
    helpers::XorByteArray(block, newBlock);
    
    if (m_mode == mode::Decrypt)
    {
        helpers::Unpadding(block);
    }

    m_data.Concatenation(block);
    m_hmacObj.MacAddBlock(block);
}

inline ByteArray AuthenticEncryptor::ProcessData(ByteArray data)
{
    if (m_mode == mode::Encrypt)
    {
        m_counter = helpers::GenerateIV();
        m_counter.Erase(0, CryptoPP::AES::BLOCKSIZE / 2);
        byte temp[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        ByteArray toConcate = ByteArray(temp, CryptoPP::AES::BLOCKSIZE / 2);
        m_counter.Concatenation(toConcate);
        m_data.Concatenation(m_counter);
        m_hmacObj.MacAddBlock(m_counter);
    }
    else if (m_mode == mode::Decrypt)
    {
        if (!m_hmacObj.VerifyMac(data.GetBlock(0, data.Size() - HMAC_OUTPUT_SIZE),
                                 data.GetBlock(data.Size() - HMAC_OUTPUT_SIZE, HMAC_OUTPUT_SIZE)))
            throw std::runtime_error("The message was corrupted");
        m_counter = helpers::ExtractIV(data);
    }
    else
    {
        throw std::exception("Fuuuuu");
    }

    size_t blocksCount = data.Size() / CryptoPP::AES::BLOCKSIZE;
    if (data.Size() % CryptoPP::AES::BLOCKSIZE != 0)
        ++blocksCount;

    for (size_t i = 0; i < blocksCount * CryptoPP::AES::BLOCKSIZE; i += CryptoPP::AES::BLOCKSIZE)
    {
        if (data.Size() - i >= CryptoPP::AES::BLOCKSIZE)
            AddBlock(data.GetBlock(i, CryptoPP::AES::BLOCKSIZE));
        else
            AddBlock(data.GetBlock(i, data.Size() - i));
    }

    if (m_mode == mode::Encrypt)
    {
        ByteArray temp = m_hmacObj.MacFinalize();
        m_data.Concatenation(temp);
    }

    return m_data;
}

}
}

#endif // __AUTH_ENCRYPTOR__
