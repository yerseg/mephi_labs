#ifndef __HMAC__
#define __HMAC__

#include "imac_provider.h"
#include "sha.h"

#define HMAC_BLOCK_SIZE 64

namespace crypto
{

namespace mac
{

class HmacProvider : public IMacProvider
{
public:

    HmacProvider();

    void SetKey(ByteArray key) override;
    ByteArray ComputeMac(ByteArray data) override;
    bool VerifyMac(ByteArray data, ByteArray tag) override;

private:

    void MacAddBlock(ByteArray dataBlock) override;
    ByteArray MacFinalize() override;

    void UpdateSha256(ByteArray dataBlock);
    ByteArray FinalSha256();

    CryptoPP::SHA256 m_shaObj;
    ByteArray m_key;
    ByteArray m_currentBlock;
    const size_t m_blockSize;
};

}
}

#endif // __HMAC__