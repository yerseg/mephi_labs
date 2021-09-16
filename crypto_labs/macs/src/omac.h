#ifndef __OMAC__
#define __OMAC__

#include "imac_provider.h"

#define OMAC_BLOCK_SIZE 16

namespace crypto
{

namespace mac
{

class OmacProvider : public IMacProvider
{
public:

    OmacProvider();

    void SetKey(ByteArray key) override;
    ByteArray ComputeMac(ByteArray data) override;
    bool VerifyMac(ByteArray data, ByteArray tag) override;

private:

    void MacAddBlock(ByteArray dataBlock) override;
    ByteArray MacFinalize() override;

    std::pair<ByteArray, ByteArray> GenerateAdditionalKeys() const;

    ByteArray m_key;
    ByteArray m_currentBlock;
    const size_t m_blockSize;
    std::pair<ByteArray, ByteArray> m_additionalKeys;
    bool m_isPadded = false;
};

}
}

#endif // __OMAC__