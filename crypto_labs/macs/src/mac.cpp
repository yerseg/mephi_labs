#include <iostream>
#include <string>

#include "omac.h"
#include "tmac.h"
#include "hmac.h"
#include "randpool.h"

using namespace crypto::mac;

int main()
{
    std::ofstream output;

    output.open(".\\report.txt", std::ios::out);

    ByteArray testKey = ByteArray(std::string("Key!Key!Key!Key!"));
    ByteArray testData = ByteArray(std::string("Hello!Hello!Hello!Hello!Hello!Hello!Hell"));

    ByteArray testDataModified = testData;
    testDataModified[0] &= 8;

    output << "Test key: " << testKey << std::endl;
    output << "Test data: " << testData << std::endl;
    output << "Test modified data: " << testDataModified << std::endl;

    OmacProvider omac;
    TruncatedMacProvider tmac;
    HmacProvider hmac;

    omac.SetKey(testKey);
    tmac.SetKey(testKey);
    hmac.SetKey(testKey);

    ByteArray omacResult = omac.ComputeMac(testData);
    ByteArray tmacResult = tmac.ComputeMac(testData);
    ByteArray hmacResult = hmac.ComputeMac(testData);

    output << "Omac: " << omacResult << std::endl;
    output << "Tmac: " << tmacResult << std::endl;
    output << "Hmac: " << hmacResult << std::endl;

    ByteArray omacResultModified = omac.ComputeMac(testDataModified);
    ByteArray tmacResultModified = tmac.ComputeMac(testDataModified);
    ByteArray hmacResultModified = hmac.ComputeMac(testDataModified);

    output << "Omac modified: " << omacResultModified << std::endl;
    output << "Tmac modified: " << tmacResultModified << std::endl;
    output << "Hmac modified: " << hmacResultModified << std::endl;

    output << "Omac verify result: " << omac.VerifyMac(testData, omac.ComputeMac(testData)) << std::endl;
    output << "Tmac verify result: " << tmac.VerifyMac(testData, tmac.ComputeMac(testData)) << std::endl;
    output << "Hmac verify result: " << hmac.VerifyMac(testData, hmac.ComputeMac(testData)) << std::endl;

    output << "Omac verify result (modified): " << omac.VerifyMac(testData, omac.ComputeMac(testDataModified)) << std::endl;
    output << "Tmac verify result (modified): " << tmac.VerifyMac(testData, tmac.ComputeMac(testDataModified)) << std::endl;
    output << "Hmac verify result (modified): " << hmac.VerifyMac(testData, hmac.ComputeMac(testDataModified)) << std::endl;

    output.close();

    output.open("output.txt", std::ios::out);

    double summTimeOmac = 0.0;
    double summTimeHmac = 0.0;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    
    CryptoPP::RandomPool prng;
    byte key[CryptoPP::AES::DEFAULT_KEYLENGTH] = { 0x00 };
    byte* data = nullptr;

    for (size_t i = 10; i < 1024 * 1024; i *= 10)
    {
        summTimeOmac = 0.0;
        summTimeHmac = 0.0;

        for (size_t j = 0; j < 1000; ++j)
        {
            prng.GenerateBlock(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
            testKey = ByteArray(key, CryptoPP::AES::DEFAULT_KEYLENGTH);

            data = new byte[i];
            prng.GenerateBlock(data, i);
            testData = ByteArray(data, i);
            delete[] data;

            start = std::chrono::system_clock::now();

            omac.SetKey(testKey);
            omac.ComputeMac(testData);

            end = std::chrono::system_clock::now();

            summTimeOmac += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;

            start = std::chrono::system_clock::now();

            hmac.SetKey(testKey);
            hmac.ComputeMac(testData);

            end = std::chrono::system_clock::now();

            summTimeHmac += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;
        }

        output << i << ' ' << summTimeOmac / 1000.0 << ' ' << summTimeHmac / 1000.0 << std::endl;
    }

    output.close();

    return 0;
}