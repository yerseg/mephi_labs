#include <fstream>
#include "auth_encryptor.h"

#define BYTES_IN_MB 1024 * 1024

using namespace crypto::auth;

int main()
{
    std::ofstream output;

    output.open(".\\report.txt", std::ios::out);

    ByteArray testKey = ByteArray(std::string("Key!Key!Key!Key!"));
    ByteArray testMacKey = ByteArray(std::string("Auh!Auh!Auh!Auh!"));
    ByteArray testData = ByteArray(std::string("Hello!Hello!Hello!Hello!Hello!Hello!Hell"));

    output << "Test key: " << testKey << std::endl;
    output << "Test data: " << testData << std::endl;

    AuthenticEncryptor encryptor(mode::Encrypt);
    encryptor.SetKey(testKey);
    encryptor.SetMacKey(testMacKey);

    ByteArray cipherMessage = encryptor.ProcessData(testData);
    ByteArray corruptedCipherMessage = cipherMessage;
    corruptedCipherMessage[corruptedCipherMessage.Size() - 1] &= 126;

    output << "Cipher Message: " << cipherMessage << std::endl;
    output << "Corrupted Cipher Message: " << corruptedCipherMessage << std::endl;

    AuthenticEncryptor decryptor(mode::Decrypt);
    decryptor.SetKey(testKey);
    decryptor.SetMacKey(testMacKey);

    try
    {
        cipherMessage = decryptor.ProcessData(cipherMessage);
        output << "Text: " << cipherMessage << std::endl;
    }
    catch (std::runtime_error& ex)
    {
        output << ex.what() << std::endl;
    }

    try
    {
        corruptedCipherMessage = decryptor.ProcessData(corruptedCipherMessage);
        output << "Corrupted text: " << corruptedCipherMessage << std::endl;
    }
    catch (std::runtime_error& ex)
    {
        output << ex.what() << std::endl;
    }

    byte* message = new byte[100 * BYTES_IN_MB];
    CryptoPP::RandomPool prng;
    prng.GenerateBlock(message, 100 * BYTES_IN_MB);
    ByteArray testMessage = ByteArray(message, 100 * BYTES_IN_MB);
    delete[] message;

    encryptor.SetKey(testKey);
    encryptor.SetMacKey(testMacKey);

    output << "Message 100MB: " << testMessage << std::endl;

    ByteArray cipherText = encryptor.ProcessData(testMessage);

    output << "Cipher Message 100MB: " << testMessage << std::endl;

    decryptor.SetKey(testKey);
    decryptor.SetMacKey(testMacKey);

    try
    {
        ByteArray plainText = decryptor.ProcessData(cipherText);
        output << "Decrypted Message 100MB: " << plainText << std::endl;
    }
    catch (std::runtime_error& ex)
    {
        output << ex.what() << std::endl;
    }

    output.close();

    return 0;
}

