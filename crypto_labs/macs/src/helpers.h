#ifndef __HELPERS__
#define __HELPERS__

#include <iostream>

#include <randpool.h>
#include <aes.h>
#include <sha.h>
#include <modes.h>

#include "../hash/bytearray.h"

#define BIT_IN_BYTE 8

namespace crypto
{

namespace helpers
{

namespace padding_type
{

enum Type
{
    MAC,
    PKCS7
};
};

inline ByteArray GenerateIV()
{
    byte output[CryptoPP::AES::BLOCKSIZE];
    CryptoPP::RandomPool prng;
    prng.GenerateBlock(output, CryptoPP::AES::BLOCKSIZE);
    return ByteArray(output, CryptoPP::AES::BLOCKSIZE);
}

inline ByteArray ExtractIV(ByteArray& data)
{
    ByteArray res = data.GetBlock(0, CryptoPP::AES::BLOCKSIZE);
    data.Erase(0, CryptoPP::AES::BLOCKSIZE);
    return res;
}

inline void AddPkcs7Padding(ByteArray& data)
{
    const size_t paddingLength = CryptoPP::AES::BLOCKSIZE - data.Size();
    byte* padding = new byte[paddingLength];
    for (size_t i = 0; i < paddingLength; ++i)
    {
        padding[i] = paddingLength;
    }
    ByteArray paddingArray = ByteArray(padding, paddingLength);
    data.Concatenation(paddingArray);
    delete[] padding;
}

inline void AddMacPadding(ByteArray& data)
{
    const size_t paddingLength = CryptoPP::AES::BLOCKSIZE - data.Size();
    byte* padding = new byte[paddingLength];
    padding[0] = 1;
    for (size_t i = 1; i < paddingLength; ++i)
    {
        padding[i] = 0;
    }
    ByteArray paddingArray = ByteArray(padding, paddingLength);
    data.Concatenation(paddingArray);
    delete[] padding;
}

inline void AddNonePadding(ByteArray& data)
{
    const size_t paddingLength = CryptoPP::AES::BLOCKSIZE - data.Size();
    byte* padding = new byte[paddingLength];
    padding[0] = 1;
    for (size_t i = 1; i < paddingLength; ++i)
    {
        padding[i] = 0;
    }
    ByteArray paddingArray = ByteArray(padding, paddingLength);
    data.Concatenation(paddingArray);
    delete[] padding;
}

inline void AddPadding(ByteArray& data, padding_type::Type type)
{
    switch (type)
    {
        case padding_type::MAC:
            AddMacPadding(data);
            break;
        case padding_type::PKCS7:
            AddPkcs7Padding(data);
            break;
    }
}

inline void Unpadding(ByteArray& data)
{
    byte value = data[data.Size() - 1];
    for (size_t i = 0; i < data.Size() && i < value; ++i)
    {
        if (data[data.Size() - i - 1] != value)
            return;
    }
    data.Erase(CryptoPP::AES::BLOCKSIZE - value, CryptoPP::AES::BLOCKSIZE);
}

inline void XorByteArray(ByteArray& first, const ByteArray& second)
{
    for (size_t i = 0, j = 0; i < first.Size() && j < second.Size(); ++i, ++j)
    {
        first[i] ^= second[j];
    }
}

inline void LeftBitShift(ByteArray& block, const size_t& num)
{
    block[block.Size() - 1] <<= num;
    byte temp;
    for (size_t i = 1; i < block.Size(); ++i)
    {
        temp = block[i] & (UCHAR_MAX << (BIT_IN_BYTE - num));
        block[i - 1] ^= temp >> (BIT_IN_BYTE - num);
        block[i] <<= num;
    }
}

inline ByteArray AesBlockEncrypt(ByteArray key, ByteArray data, padding_type::Type paddingType)
{
    if (data.Size() > CryptoPP::AES::BLOCKSIZE)
        throw std::runtime_error("The length of the block is greater than the maximum allowed!");
    if (key.Size() < CryptoPP::AES::MIN_KEYLENGTH || key.Size() > CryptoPP::AES::MAX_KEYLENGTH)
        throw std::runtime_error("Invalid key length!");
    if (data.Size() < CryptoPP::AES::BLOCKSIZE)
        AddPadding(data, paddingType);

    byte out[CryptoPP::AES::BLOCKSIZE] = { 0 };
    CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption  ecbEncryption(key.Data(), key.Size());
    ecbEncryption.ProcessData(out, data.Data(), data.Size());
    return ByteArray(out, CryptoPP::AES::BLOCKSIZE);
}

}
}

#endif // __HELPERS__