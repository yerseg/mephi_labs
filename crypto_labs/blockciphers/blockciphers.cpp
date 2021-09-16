#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

#include <hex.h>
#include <randpool.h>
#include <aes.h>
#include <modes.h>

#include "../hash/bytearray.h"

#define ONE_HUNDRED 100
#define TASK_TEXT_SIZE 2.5
#define ZERO 0

namespace cipher_mode
{
    enum Modes
    {
        ECB,
        CBC,
        CFB,
        OFB,
        CTR
    };
}

ByteArray GenerateIV()
{
    byte output[CryptoPP::AES::BLOCKSIZE];
    CryptoPP::RandomPool prng;
    prng.GenerateBlock(output, CryptoPP::AES::BLOCKSIZE);
    return ByteArray(output, CryptoPP::AES::BLOCKSIZE);
}

ByteArray ExtractIV(ByteArray& data)
{
    ByteArray res = data.GetBlock(ZERO, CryptoPP::AES::BLOCKSIZE);
    data.Erase(ZERO, CryptoPP::AES::BLOCKSIZE);
    return res;
}

void AddPkcs7Padding(ByteArray& data)
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

void Unpadding(ByteArray& data)
{
    byte value = data[data.Size() - 1];
    for (size_t i = 0; i < data.Size() && i < value; ++i)
    {
        if (data[data.Size() - i - 1] != value)
            return;
    }    
    data.Erase(CryptoPP::AES::BLOCKSIZE - value, CryptoPP::AES::BLOCKSIZE);
}

void XorByteArray(ByteArray& first, const ByteArray& second)
{
    for (size_t i = 0, j = 0; i < first.Size() && j < second.Size(); ++i, ++j)
    {
        first[i] ^= second[j];
    }
}

ByteArray AesBlockEncrypt(ByteArray key, ByteArray data)
{
    if (data.Size() > CryptoPP::AES::BLOCKSIZE)
        throw std::runtime_error("The length of the block is greater than the maximum allowed!");
    if (key.Size() < CryptoPP::AES::MIN_KEYLENGTH || key.Size() > CryptoPP::AES::MAX_KEYLENGTH)
        throw std::runtime_error("Invalid key length!");
    if (data.Size() < CryptoPP::AES::BLOCKSIZE)
        AddPkcs7Padding(data);

    byte out[CryptoPP::AES::BLOCKSIZE] = { ZERO };
    CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption  ecbEncryption(key.Data(), key.Size());
    ecbEncryption.ProcessData(out, data.Data(), data.Size());
    return ByteArray(out, CryptoPP::AES::BLOCKSIZE);
};

ByteArray AesBlockDecrypt(ByteArray key, ByteArray data)
{
    if (data.Size() > CryptoPP::AES::BLOCKSIZE)
        throw std::runtime_error("The length of the block is greater than the maximum allowed!");
    if (key.Size() < CryptoPP::AES::MIN_KEYLENGTH || key.Size() > CryptoPP::AES::MAX_KEYLENGTH)
        throw std::runtime_error("Invalid key length!");
    if (data.Size() < CryptoPP::AES::BLOCKSIZE)
        AddPkcs7Padding(data);

    byte out[CryptoPP::AES::BLOCKSIZE] = { ZERO };
    CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption  ecbDecryption(key.Data(), key.Size());
    ecbDecryption.ProcessData(out, data.Data(), data.Size());
    ByteArray decryptData = ByteArray(out, CryptoPP::AES::BLOCKSIZE);
    Unpadding(decryptData);
    return decryptData;
};

ByteArray EcbModeAesEncrypt(ByteArray key, ByteArray data)
{
    size_t blocksCount = data.Size() / CryptoPP::AES::BLOCKSIZE;
    if (data.Size() % CryptoPP::AES::BLOCKSIZE != ZERO)
        ++blocksCount;

    ByteArray cipherText;
    for (size_t i = 0; i < blocksCount * CryptoPP::AES::BLOCKSIZE; i += CryptoPP::AES::BLOCKSIZE)
    {
        ByteArray newBlock;

        if (data.Size() - i >= CryptoPP::AES::BLOCKSIZE)
            newBlock = AesBlockEncrypt(key, data.GetBlock(i, CryptoPP::AES::BLOCKSIZE));
        else
            newBlock = AesBlockEncrypt(key, data.GetBlock(i, data.Size() - i));

        cipherText.Concatenation(newBlock);
    }

    return cipherText;
}

ByteArray EcbModeAesDecrypt(ByteArray key, ByteArray data)
{
    size_t blocksCount = data.Size() / CryptoPP::AES::BLOCKSIZE;
    if (data.Size() % CryptoPP::AES::BLOCKSIZE != 0)
        ++blocksCount;

    ByteArray plainText;
    for (size_t i = 0; i < blocksCount * CryptoPP::AES::BLOCKSIZE; i += CryptoPP::AES::BLOCKSIZE)
    {
        ByteArray newBlock;

        if (data.Size() - i >= CryptoPP::AES::BLOCKSIZE)
            newBlock = AesBlockDecrypt(key, data.GetBlock(i, CryptoPP::AES::BLOCKSIZE));
        else
            newBlock = AesBlockDecrypt(key, data.GetBlock(i, data.Size() - i));

        plainText.Concatenation(newBlock);
    }

    return plainText;
}

ByteArray CbcModeAesEncrypt(ByteArray key, ByteArray data)
{
    ByteArray cipherText;
    ByteArray iv = GenerateIV();
    cipherText.Concatenation(iv);

    size_t blocksCount = data.Size() / CryptoPP::AES::BLOCKSIZE;
    if (data.Size() % CryptoPP::AES::BLOCKSIZE != 0)
        ++blocksCount;

    for (size_t i = 0; i < blocksCount * CryptoPP::AES::BLOCKSIZE; i += CryptoPP::AES::BLOCKSIZE)
    {
        ByteArray encryptedBlock;

        if (data.Size() - i >= CryptoPP::AES::BLOCKSIZE)
            encryptedBlock = data.GetBlock(i, CryptoPP::AES::BLOCKSIZE);
        else
            encryptedBlock = data.GetBlock(i, data.Size() - i);

        XorByteArray(encryptedBlock, iv);
        encryptedBlock = AesBlockEncrypt(key, encryptedBlock);

        cipherText.Concatenation(encryptedBlock);
        iv = encryptedBlock;
    }

    return cipherText;
}

ByteArray CbcModeAesDecrypt(ByteArray key, ByteArray data)
{
    ByteArray iv = ExtractIV(data);

    size_t blocksCount = data.Size() / CryptoPP::AES::BLOCKSIZE;
    if (data.Size() % CryptoPP::AES::BLOCKSIZE != 0)
        ++blocksCount;

    ByteArray plainText;
    for (size_t i = 0; i < blocksCount * CryptoPP::AES::BLOCKSIZE; i += CryptoPP::AES::BLOCKSIZE)
    {
        ByteArray decryptedBlock;
        if (data.Size() - i >= CryptoPP::AES::BLOCKSIZE)
        {
            decryptedBlock = data.GetBlock(i, CryptoPP::AES::BLOCKSIZE);
        }
        else
        {
            decryptedBlock = data.GetBlock(i, data.Size() - i);
        }

        ByteArray tmp = decryptedBlock;
        
        decryptedBlock = AesBlockDecrypt(key, decryptedBlock);
        XorByteArray(decryptedBlock, iv);

        iv = tmp;

        Unpadding(decryptedBlock);
        plainText.Concatenation(decryptedBlock);
    }

    return plainText;
}

ByteArray CfbModeAesEncrypt(ByteArray key, ByteArray data)
{
    ByteArray cipherText;
    ByteArray iv = GenerateIV();
    cipherText.Concatenation(iv);

    size_t blocksCount = data.Size() / CryptoPP::AES::BLOCKSIZE;
    if (data.Size() % CryptoPP::AES::BLOCKSIZE != 0)
        ++blocksCount;

    for (size_t i = 0; i < blocksCount * CryptoPP::AES::BLOCKSIZE; i += CryptoPP::AES::BLOCKSIZE)
    {
        ByteArray encryptedBlock = AesBlockEncrypt(key, iv);
        if (data.Size() - i >= CryptoPP::AES::BLOCKSIZE)
            XorByteArray(encryptedBlock, data.GetBlock(i, CryptoPP::AES::BLOCKSIZE));
        else
        {
            XorByteArray(encryptedBlock, data.GetBlock(i, data.Size() - i));
            encryptedBlock.Erase(data.Size() - i, encryptedBlock.Size());
        }
            
        cipherText.Concatenation(encryptedBlock);
        iv = encryptedBlock;
    }

    return cipherText;
}

ByteArray CfbModeAesDecrypt(ByteArray key, ByteArray data)
{
    ByteArray plainText;
    ByteArray iv = ExtractIV(data);

    size_t blocksCount = data.Size() / CryptoPP::AES::BLOCKSIZE;
    if (data.Size() % CryptoPP::AES::BLOCKSIZE != 0)
        ++blocksCount;

    for (size_t i = 0; i < blocksCount * CryptoPP::AES::BLOCKSIZE; i += CryptoPP::AES::BLOCKSIZE)
    {
        ByteArray decryptedBlock = AesBlockEncrypt(key, iv);
        if (data.Size() - i >= CryptoPP::AES::BLOCKSIZE)
            iv = data.GetBlock(i, CryptoPP::AES::BLOCKSIZE);
        else
            iv = data.GetBlock(i, data.Size() - i);

        XorByteArray(decryptedBlock, iv);
        if (iv.Size() < CryptoPP::AES::BLOCKSIZE)
            decryptedBlock.Erase(data.Size() - i, decryptedBlock.Size());

        Unpadding(decryptedBlock);
        plainText.Concatenation(decryptedBlock);
    }

    return plainText;
}

ByteArray OfbModeAesEncrypt(ByteArray key, ByteArray data)
{
    ByteArray cipherText;
    ByteArray iv = GenerateIV();
    cipherText.Concatenation(iv);

    size_t blocksCount = data.Size() / CryptoPP::AES::BLOCKSIZE;
    if (data.Size() % CryptoPP::AES::BLOCKSIZE != 0)
        ++blocksCount;

    for (size_t i = 0; i < blocksCount * CryptoPP::AES::BLOCKSIZE; i += CryptoPP::AES::BLOCKSIZE)
    {
        ByteArray encryptedBlock = AesBlockEncrypt(key, iv);
        iv = encryptedBlock;

        if (data.Size() - i >= CryptoPP::AES::BLOCKSIZE)
            XorByteArray(encryptedBlock, data.GetBlock(i, CryptoPP::AES::BLOCKSIZE));
        else
        {
            XorByteArray(encryptedBlock, data.GetBlock(i, data.Size() - i));
            encryptedBlock.Erase(data.Size() - i, encryptedBlock.Size());
        }

        cipherText.Concatenation(encryptedBlock);
    }

    return cipherText;
}

ByteArray OfbModeAesDecrypt(ByteArray key, ByteArray data)
{
    ByteArray plainText;
    ByteArray iv = ExtractIV(data);

    size_t blocksCount = data.Size() / CryptoPP::AES::BLOCKSIZE;
    if (data.Size() % CryptoPP::AES::BLOCKSIZE != 0)
        ++blocksCount;

    for (size_t i = 0; i < blocksCount * CryptoPP::AES::BLOCKSIZE; i += CryptoPP::AES::BLOCKSIZE)
    {
        ByteArray decryptedBlock = AesBlockEncrypt(key, iv);
        iv = decryptedBlock;

        ByteArray tmp;
        if (data.Size() - i >= CryptoPP::AES::BLOCKSIZE)
            tmp = data.GetBlock(i, CryptoPP::AES::BLOCKSIZE);
        else
            tmp = data.GetBlock(i, data.Size() - i);

        XorByteArray(decryptedBlock, tmp);
        if (tmp.Size() < CryptoPP::AES::BLOCKSIZE)
            decryptedBlock.Erase(data.Size() - i, decryptedBlock.Size());

        Unpadding(decryptedBlock);
        plainText.Concatenation(decryptedBlock);
    }

    return plainText;
}

void IncrementByteArray(ByteArray& array)
{
    for (size_t i = 0; i < array.Size(); ++i)
    {
        if (array[array.Size() - 1 - i] == UCHAR_MAX)
        {
            array[array.Size() - 1 - i] = ZERO;
        }
        else
        {
            ++array[array.Size() - 1 - i];
            break;
        }
    }
}

ByteArray CtrModeAesEncrypt(ByteArray key, ByteArray data)
{
    ByteArray cipherText;
    ByteArray counter = GenerateIV();
    counter.Erase(0, CryptoPP::AES::BLOCKSIZE / 2);

    byte temp[] = { ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO };
    ByteArray toConcate = ByteArray(temp, CryptoPP::AES::BLOCKSIZE / 2);
    counter.Concatenation(toConcate);

    cipherText.Concatenation(counter);

    size_t blocksCount = data.Size() / CryptoPP::AES::BLOCKSIZE;
    if (data.Size() % CryptoPP::AES::BLOCKSIZE != 0)
        ++blocksCount;

    for (size_t i = 0; i < blocksCount * CryptoPP::AES::BLOCKSIZE; i += CryptoPP::AES::BLOCKSIZE)
    {
        ByteArray encryptedBlock = AesBlockEncrypt(key, counter);
        IncrementByteArray(counter);

        if (data.Size() - i >= CryptoPP::AES::BLOCKSIZE)
            XorByteArray(encryptedBlock, data.GetBlock(i, CryptoPP::AES::BLOCKSIZE));
        else
        {
            XorByteArray(encryptedBlock, data.GetBlock(i, data.Size() - i));
            encryptedBlock.Erase(data.Size() - i, encryptedBlock.Size());
        }

        cipherText.Concatenation(encryptedBlock);
    }

    return cipherText;
}

ByteArray CtrModeAesDecrypt(ByteArray key, ByteArray data)
{
    ByteArray plainText;
    ByteArray counter = ExtractIV(data);

    size_t blocksCount = data.Size() / CryptoPP::AES::BLOCKSIZE;
    if (data.Size() % CryptoPP::AES::BLOCKSIZE != 0)
        ++blocksCount;

    for (size_t i = 0; i < blocksCount * CryptoPP::AES::BLOCKSIZE; i += CryptoPP::AES::BLOCKSIZE)
    {
        ByteArray decryptedBlock = AesBlockEncrypt(key, counter);
        IncrementByteArray(counter);

        ByteArray tmp;
        if (data.Size() - i >= CryptoPP::AES::BLOCKSIZE)
            tmp = data.GetBlock(i, CryptoPP::AES::BLOCKSIZE);
        else
            tmp = data.GetBlock(i, data.Size() - i);

        XorByteArray(decryptedBlock, tmp);

        if (tmp.Size() < CryptoPP::AES::BLOCKSIZE)
            decryptedBlock.Erase(data.Size() - i, decryptedBlock.Size());

        Unpadding(decryptedBlock);
        plainText.Concatenation(decryptedBlock);
    }

    return plainText;
}

ByteArray AesEncrypt(ByteArray key, ByteArray data, cipher_mode::Modes mode)
{
    switch (mode)
    {
        case cipher_mode::ECB:
            return EcbModeAesEncrypt(key, data);

        case cipher_mode::CBC:
            return CbcModeAesEncrypt(key, data);

        case cipher_mode::CFB:
            return CfbModeAesEncrypt(key, data);

        case cipher_mode::CTR:
            return CtrModeAesEncrypt(key, data);

        case cipher_mode::OFB:
            return OfbModeAesEncrypt(key, data);

        default:
            throw std::runtime_error("");
    }
}

ByteArray AesDecrypt(ByteArray key, ByteArray data, cipher_mode::Modes mode)
{
    switch (mode)
    {
        case cipher_mode::ECB:
            return EcbModeAesDecrypt(key, data);

        case cipher_mode::CBC:
            return CbcModeAesDecrypt(key, data);

        case cipher_mode::CFB:
            return CfbModeAesDecrypt(key, data);

        case cipher_mode::CTR:
            return CtrModeAesDecrypt(key, data);

        case cipher_mode::OFB:
            return OfbModeAesDecrypt(key, data);

        default:
            throw std::runtime_error("");
    }
}

bool CbcModeValidation()
{
    std::string testKey = "HELLOO, IT`S ME!";
    std::string testStr = "Hello, World! Hello, World! Hello, World! Hello, World! Hello, W";

    ByteArray key = ByteArray(testKey);
    ByteArray testData = ByteArray(testStr);

    ByteArray outArray = AesEncrypt(key, testData, cipher_mode::CBC);
    byte out[ONE_HUNDRED] = { ZERO };
    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption  ecbEncryption(key.Data(), key.Size(), outArray.GetBlock(0, CryptoPP::AES::BLOCKSIZE).Data());
    ecbEncryption.ProcessData(out, testData.Data(), testData.Size());

    for (size_t i = 0; i < outArray.Size() - CryptoPP::AES::BLOCKSIZE; ++i)
    {
        if (outArray[i + CryptoPP::AES::BLOCKSIZE] != out[i])
            return false;
    }

    return true;
}

//Copy-Past

int Char2Int(char input)
{
    if (input >= '0' && input <= '9')
        return input - '0';
    if (input >= 'A' && input <= 'F')
        return input - 'A' + 10;
    if (input >= 'a' && input <= 'f')
        return input - 'a' + 10;
    throw std::invalid_argument("Invalid input string");
}

#define HEX 16

void Hex2Bin(const char* src, byte* target)
{
    while (*src && src[1])
    {
        *(target++) = Char2Int(*src) * HEX + Char2Int(src[1]);
        src += 2;
    }
}

//

int main()
{
    std::cout << "-------------------VALIDATION----------------------" << std::endl;
    bool result = CbcModeValidation();
    std::cout << "Validation has completed ";
    if (result)
        std::cout << "successfully!";
    else
        std::cout << "unsuccessfully!";
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "-----------------TEXT_DECRYPTION-------------------" << std::endl;

    std::string cbcKey_1 = "140b41b22a29beb4061bda66b6747e14";
    std::string cbcCipher_1 = "4ca00ff4c898d61e1edbf1800618fb2828a226d160dad07883d04e008a7897ee2e4b7465d5290d0c0e6c6822236e1daafb94ffe0c5da05d9476be028ad7c1d81";

    std::string cbcKey_2 = "140b41b22a29beb4061bda66b6747e14";
    std::string cbcCipher_2 = "5b68629feb8606f9a6667670b75b38a5b4832d0f26e1ab7da33249de7d4afc48e713ac646ace36e872ad5fb8a512428a6e21364b0c374df45503473c5242a253";

    std::string ctrKey_1 = "36f18357be4dbd77f050515c73fcf9f2";
    std::string ctrCipher_1 = "69dda8455c7dd4254bf353b773304eec0ec7702330098ce7f7520d1cbbb20fc388d1b0adb5054dbd7370849dbf0b88d393f252e764f1f5f7ad97ef79d59ce29f5f51eeca32eabedd9afa9329";

    std::string ctrKey_2 = "36f18357be4dbd77f050515c73fcf9f2";
    std::string ctrCipher_2 = "770b80259ec33beb2561358a9f2dc617e46218c0a53cbeca695ae45faa8952aa0e311bde9d4e01726d3184c34451";

    std::vector<std::pair<std::string, std::string>> vec = { { cbcKey_1, cbcCipher_1 }, { cbcKey_2, cbcCipher_2 }, { ctrKey_1, ctrCipher_1 }, { ctrKey_2, ctrCipher_2 } };
    for (size_t i = 0; i < 2; ++i)
    {
        byte* key = new byte[vec[i].first.size() / 2];
        byte* cipher = new byte[vec[i].second.size() / 2];

        Hex2Bin(vec[i].first.c_str(), key);
        Hex2Bin(vec[i].second.c_str(), cipher);

        ByteArray text = AesDecrypt(ByteArray(key, vec[i].first.size() / 2), ByteArray(cipher, vec[i].second.size() / 2), cipher_mode::CBC);
        std::string output(reinterpret_cast<const char*>(text.Data()), text.Size());

        std::cout << "Text_" << i << " : " << output << std::endl;

        delete[] key;
        delete[] cipher;
    }

    for (size_t i = 2; i < 4; ++i)
    {
        byte* key = new byte[vec[i].first.size() / 2];
        byte* cipher = new byte[vec[i].second.size() / 2];

        Hex2Bin(vec[i].first.c_str(), key);
        Hex2Bin(vec[i].second.c_str(), cipher);

        ByteArray text = AesDecrypt(ByteArray(key, vec[i].first.size() / 2), ByteArray(cipher, vec[i].second.size() / 2), cipher_mode::CTR);
        std::string output(reinterpret_cast<const char*>(text.Data()), text.Size());

        std::cout << "Text_" << i << " : " << output << std::endl;

        delete[] key;
        delete[] cipher;
    }

    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "----------------RANDOM_ENCRYPTION-DECRYPTION_2.5blocks-------------------------" << std::endl;

    byte output[ONE_HUNDRED];
    CryptoPP::RandomPool prng;
    prng.GenerateBlock(output, CryptoPP::AES::BLOCKSIZE * TASK_TEXT_SIZE);
    ByteArray text = ByteArray(output, CryptoPP::AES::BLOCKSIZE * TASK_TEXT_SIZE);

    prng.GenerateBlock(output, CryptoPP::AES::MIN_KEYLENGTH);
    ByteArray key = ByteArray(output, CryptoPP::AES::MIN_KEYLENGTH);

    ByteArray ecb, cbc, cfb, ofb, ctr;
    std::cout << "Key in hex: " << key << std::endl;
    std::cout << "Text in hex: " << text << std::endl;

    ecb = AesEncrypt(key, text, cipher_mode::ECB);
    cbc = AesEncrypt(key, text, cipher_mode::CBC);
    cfb = AesEncrypt(key, text, cipher_mode::CFB);
    ofb = AesEncrypt(key, text, cipher_mode::OFB);
    ctr = AesEncrypt(key, text, cipher_mode::CTR);

    std::cout << "Encrypted Text (HEX) in ECB: " << ecb << std::endl;
    std::cout << "Encrypted Text (HEX) in CBC: " << cbc << std::endl;
    std::cout << "Encrypted Text (HEX) in CFB: " << cfb << std::endl;
    std::cout << "Encrypted Text (HEX) in OFB: " << ofb << std::endl;
    std::cout << "Encrypted Text (HEX) in CTR: " << ctr << std::endl;

    ecb = AesDecrypt(key, ecb, cipher_mode::ECB);
    cbc = AesDecrypt(key, cbc, cipher_mode::CBC);
    cfb = AesDecrypt(key, cfb, cipher_mode::CFB);
    ofb = AesDecrypt(key, ofb, cipher_mode::OFB);
    ctr = AesDecrypt(key, ctr, cipher_mode::CTR);

    std::cout << "Decrypted Text (HEX) in ECB: " << ecb << std::endl;
    std::cout << "Decrypted Text (HEX) in CBC: " << cbc << std::endl;
    std::cout << "Decrypted Text (HEX) in CFB: " << cfb << std::endl;
    std::cout << "Decrypted Text (HEX) in OFB: " << ofb << std::endl;
    std::cout << "Decrypted Text (HEX) in CTR: " << ctr << std::endl;


    return 0;
}