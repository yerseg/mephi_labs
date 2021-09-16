#ifndef __MAC_PROVIDER__
#define __MAC_PROVIDER__

#include "../hash/bytearray.h"

namespace crypto
{

namespace mac
{

struct IMacProvider
{
    virtual void SetKey(ByteArray key) = 0;

    virtual ByteArray ComputeMac(ByteArray data) = 0;

    virtual bool VerifyMac(ByteArray data, ByteArray tag) = 0;

    virtual ~IMacProvider() = default;

protected:

    virtual void MacAddBlock(ByteArray dataBlock) = 0;

    virtual ByteArray MacFinalize() = 0;
};

}
}

#endif // __MAC_PROVIDER__
