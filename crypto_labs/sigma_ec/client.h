#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <unordered_map>
#include <string>

#include <queue.h>
#include <speck.h>

namespace CryptoPP
{
using SecByteBlockPair = std::pair<SecByteBlock, SecByteBlock>;
}

using namespace CryptoPP;

class Client
{
public:
    explicit Client(const std::string& clientName);

    void SetSignatureFriendKey(const std::string& friendName, const ByteQueue& key);
    void SetFriendDataForSharedSecret(const std::string& name, const SecByteBlockPair& keys);

    std::string GetName() const;
    ByteQueue GetSignaturePublicKey() const;
    SecByteBlockPair GetDataForSharedSecret(Client& receiver);
    std::vector<SecByteBlock> GetSignatureAndData(const std::string& name);

    void Connect(const std::vector<SecByteBlock>& data);
    void ComputeSharedKeys(const std::string& name);

    SecByteBlock SendMessage(const std::string& message);
    std::string ReceiveMessage(const SecByteBlock& message);

private:
    void SetOrder(const std::string& name, bool status);

    const std::string m_clientName;
    ByteQueue m_ecdsaSK;
    ByteQueue m_ecdsaPK;
    SecByteBlock m_dhSK;
    SecByteBlock m_dhPK;
    SecByteBlock m_sharedM;
    SecByteBlock m_sharedE;
    SecByteBlock m_r;
    std::unordered_map<std::string, std::pair<ByteQueue, SecByteBlockPair>> m_friendKeys;
    std::unordered_map<std::string, bool> m_isFirstForCompute;
};


#endif // __CLIENT_H__
