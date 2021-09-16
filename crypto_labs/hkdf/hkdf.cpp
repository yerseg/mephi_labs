#include <fstream>
#include <vector>
#include <sha.h>
#include <hex.h>
#include <randpool.h>

using byte = unsigned char;
using ByteArray = std::vector<byte>; //ДОЛГО, но не надо парить мозги

#define OPAD 0x5C
#define IPAD 0x36
#define BITMASK 0x1F
#define KEYSCOUNT 1000

ByteArray StringToByteArray(std::string str)
{
    ByteArray byteArray(str.size());
    for (size_t i = 0; i < str.size(); i++)
    {
        byteArray[i] = static_cast<byte>(str[i]);
    }
    return byteArray;
}

ByteArray CArrayToByteArray(byte* bytePtr, const size_t length)
{
    ByteArray byteArray(length);
    for (size_t i = 0; i < length; i++)
    {
        byteArray[i] = bytePtr[i];
    }
    return byteArray;
}

ByteArray Sha256(ByteArray data)
{
    CryptoPP::SHA256 hash;
    byte digest[CryptoPP::SHA256::DIGESTSIZE];
    hash.CalculateDigest(digest, data.data(), data.size());
    return CArrayToByteArray(digest, CryptoPP::SHA256::DIGESTSIZE);
}

ByteArray HmacSha256(ByteArray key, ByteArray data)
{
    if (key.size() > CryptoPP::SHA256::BLOCKSIZE)
        key = Sha256(key);
    if (key.size() < CryptoPP::SHA256::BLOCKSIZE)
        key.insert(key.end(), CryptoPP::SHA256::BLOCKSIZE - key.size(), 0x0);

    ByteArray firstOperand = key;
    ByteArray secondOperand = key;

    for (size_t i = 0; i < CryptoPP::SHA256::BLOCKSIZE; i++)
    {
        firstOperand[i] ^= OPAD;
        secondOperand[i] ^= IPAD;
    }

    secondOperand.insert(secondOperand.end(), data.begin(), data.end());
    secondOperand = Sha256(secondOperand);
    firstOperand.insert(firstOperand.end(), secondOperand.begin(), secondOperand.end());
    ByteArray hmac = Sha256(firstOperand);
    return hmac;
}

ByteArray HkdfExtract(ByteArray xts, ByteArray skm)
{
    return HmacSha256(xts, skm);
}

ByteArray HkdfExpand(ByteArray prk, ByteArray lastKey, ByteArray ctx, int i)
{
    lastKey.insert(lastKey.end(), ctx.begin(), ctx.end());
    lastKey.push_back(i);
    return HmacSha256(prk, lastKey);
}

// keyLength in bytes
ByteArray Pbkdf2(const ByteArray password, ByteArray salt, const int iterationsCount, const int keyLength)
{
    const int length = keyLength / CryptoPP::SHA256::DIGESTSIZE;
    ByteArray key;
	
    for (size_t i = 0; i < length; i++)
    {
        ByteArray numberForConcatenation(sizeof(i), 0);
        for (size_t l = 0; l < numberForConcatenation.size(); l++)
        {
            numberForConcatenation[l] = (i >> (8 * l)) & 0xFF;
        }
        size_t counter = 0;
        for (size_t l = 0; l < numberForConcatenation.size(); l++)
        {
	        if (numberForConcatenation[numberForConcatenation.size() - 1 - l] != 0)
	        {
		        break;
	        }
	        counter++;
        }
        numberForConcatenation.erase(numberForConcatenation.begin() + numberForConcatenation.size() - counter, numberForConcatenation.end());
    	
        salt.insert(salt.end(), numberForConcatenation.begin(), numberForConcatenation.end());
        std::vector<ByteArray> blocksArray;
    	blocksArray.push_back(HmacSha256(password, salt));
    	
        for (size_t j = 1; j < iterationsCount; j++)
        {
			blocksArray.push_back(HmacSha256(password, blocksArray[j - 1]));
        }

    	for (size_t j = 0; j < blocksArray.size(); j++)
    	{
    		for (size_t m = 0; m < CryptoPP::SHA256::DIGESTSIZE; m++)
    		{
                blocksArray[0][m] ^= blocksArray[j][m];
    		}
    	}
        key.insert(key.end(), blocksArray[0].begin(), blocksArray[0].end());
    }

    return key;
}

int main()
{
    std::ifstream in;
    in.open("\\temperature.pickle", std::ios::in);
    std::string data;
    std::string input;
	while(in)
	{
        std::getline(in, input);
        data.insert(data.end(), input.begin(), input.end());
	}
    in.close();

    std::vector<ByteArray> keyArrayHkdf;
    ByteArray ctx = { 'y', 'e', 'r', 's', 'e', 'g' };
    CryptoPP::RandomPool prng;
    byte output[CryptoPP::SHA256::DIGESTSIZE];
	
    for (size_t i = 0; i < KEYSCOUNT; i++)
    {
        prng.GenerateBlock(output, CryptoPP::SHA256::DIGESTSIZE);
        ByteArray xts = CArrayToByteArray(output, 32);
        ByteArray prk = HkdfExtract(xts, StringToByteArray(data));
    	if (i == 0)
    	{
            keyArrayHkdf.push_back(HkdfExpand(prk, { 0x0 }, ctx, i));
    	}
        else
        {
            keyArrayHkdf.push_back(HkdfExpand(prk, keyArrayHkdf[i - 1], ctx, i));
        }
    }
	
    std::ofstream out;
    out.open("files\\hkdf_bits.txt", std::ios::out);
	for (auto i = 0; i < KEYSCOUNT; i++)
	{
        byte key = keyArrayHkdf[i][CryptoPP::SHA256::DIGESTSIZE - 1];
        out << (key & BITMASK) << std::endl;
	}
    out.close();

    in.open("files\\passwords.txt", std::ios::in);
    out.open("files\\pbkdf2_bits.txt", std::ios::out);
    std::string password;
	while (in)
	{
        getline(in, password);
        prng.GenerateBlock(output, CryptoPP::SHA256::DIGESTSIZE);
        ByteArray xts = CArrayToByteArray(output, 32);
        out << (Pbkdf2(StringToByteArray(password), xts, 10000, 64)[63] & BITMASK) << std::endl;
	}
    in.close();
    out.close();
	
    return 0;
}

