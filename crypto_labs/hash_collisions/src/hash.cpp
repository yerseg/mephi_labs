#include <fstream>
#include <iostream>
#include <map>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <cmath>
#include <set>

#include <sha.h>
#include <hex.h>
#include <randpool.h>

#include "bytearray.h"

#define BYTE_SIZE 8
#define BYTE_SIZE_FLOAT 8.0
#define SHA256_BIT_SIZE 256
#define FULL_BYTE 0xFF
#define CONST_FOR_LENGTH 64
#define CONST_FOR_PI 4
#define THREAD_COUNT 2
#define NUMBER_OF_COLLISIONS 100
#define FIRST_SHA_SIZE_VALUE 8
#define LAST_SHA_SIZE_VALUE 30
#define FLOAT_ONE_THOUSAND_CONST 1000.0

std::mutex mapMutex;
std::map<ByteArray, std::pair<int, int>> map;   // map[hashValue] = { iterationsCount, threadNumber }
std::pair<int, int> itersAndThread = { 0, 0 };             // pair = { iterationsCount, threadNumber }
std::atomic_int32_t memUse = 0;
std::atomic_bool isFound = false;

ByteArray Sha256(ByteArray data)
{
    CryptoPP::SHA256 hash;
    byte digest[CryptoPP::SHA256::DIGESTSIZE];
    hash.CalculateDigest(digest, data.Data(), data.Size());
    return ByteArray(digest, CryptoPP::SHA256::DIGESTSIZE);
}

ByteArray ShaXx(ByteArray data, int shaSize)
{
    if (shaSize > SHA256_BIT_SIZE)
        throw std::exception();
    ByteArray hash = Sha256(data);
    size_t countOfBytes = std::ceil(shaSize / BYTE_SIZE_FLOAT);
    hash.Erase(countOfBytes, hash.Size());
    if (shaSize % BYTE_SIZE != 0)
        hash[hash.Size() - 1] &= (FULL_BYTE >> (BYTE_SIZE - (shaSize - BYTE_SIZE * (shaSize / BYTE_SIZE))));

    return hash;
}

std::pair<ByteArray, ByteArray> FindCollision(int shaSize)
{
    memUse = 0;
    std::map<ByteArray, ByteArray> map;
    CryptoPP::RandomPool prng;
    for (;;)
    {
        CryptoPP::word32 randomInt = prng.GenerateWord32() % CONST_FOR_LENGTH;
        byte* output = static_cast<byte*>(malloc(randomInt));
        prng.GenerateBlock(output, randomInt);

        ByteArray x = ByteArray(output, randomInt);
        ByteArray hash = ShaXx(x, shaSize);

        if (map.contains(hash) && map[hash] != x)
        {
            memUse += map.size() * std::ceil(shaSize / BYTE_SIZE_FLOAT);
            return { x, map[hash] };
        }
           
        map[hash] = x;
        free(output);
    }
}

ByteArray PiTransform(ByteArray x, int shaSize)
{
    byte array[CONST_FOR_PI] = { 0 };
    ByteArray ret = ByteArray(array, CONST_FOR_PI); 
    ByteArray toConcate = ShaXx(x, shaSize);
    ret.Concatenation(toConcate);
    return ret;
}

bool CheckValue(ByteArray& value, int q)
{
    size_t count = q / BYTE_SIZE;
    if (count * BYTE_SIZE < q)
        count++;
    int unusedCount = q;
    for (size_t i = 0; i < count; ++i)
    {
        size_t countOfBits = unusedCount;
        if (countOfBits > BYTE_SIZE)
            countOfBits = BYTE_SIZE;
        if ((value[i] & (FULL_BYTE << (BYTE_SIZE - countOfBits))) != 0)
            return false;
        unusedCount -= countOfBits;
        if (unusedCount == 0)
            break;
    }
    return true;
}

void StartIteration(ByteArray initValue, ByteArray& result, int shaSize, int threadNumber, int q)
{
    ByteArray oldValue = initValue;
    
    size_t iterationsCount = 0;
        
    while(!isFound)
    {
        iterationsCount++;
        ByteArray newValue = PiTransform(oldValue, shaSize);
        if (CheckValue(newValue, q))
        {
            // SYNC
            {
                std::lock_guard<std::mutex> locker(mapMutex);
                if (map.contains(newValue) && !isFound)
                {
                    isFound = true;
                    result = newValue;
                    itersAndThread.first = iterationsCount;
                    itersAndThread.second = threadNumber;
                    memUse += map.size() * (sizeof(int) * 2 + std::ceil(shaSize / BYTE_SIZE_FLOAT));
                    return;
                }
                map[newValue] = { iterationsCount, threadNumber };
            }
        }
        oldValue = newValue;
    }
}

std::pair<ByteArray, ByteArray> CalculateCollision(ByteArray& first, ByteArray& second, int d, int shaSize)
{
    for (size_t i = 0; i < d; ++i)
    {
        first = PiTransform(first, shaSize);
    }
       
    while (true)
    {
        ByteArray firstValue = PiTransform(first, shaSize);
        ByteArray secondValue = PiTransform(second, shaSize);
        if (firstValue == secondValue)
        {
            return { first, second };
        }
        first = firstValue;
        second = secondValue;
    }
}

std::pair<ByteArray, ByteArray> FindCollisionByRhoMethod(int shaSize)
{
    // Clean
    map.clear();
    itersAndThread = { 0, 0 };
    memUse = 0;
    isFound = false;
    
    //
    CryptoPP::RandomPool prng;
    CryptoPP::word32 randomInt = prng.GenerateWord32() % CONST_FOR_LENGTH;
    byte* output = static_cast<byte*>(malloc(randomInt));

    prng.GenerateBlock(output, randomInt);
    ByteArray firstInitValue = ByteArray(output, randomInt);
    prng.GenerateBlock(output, randomInt);
    ByteArray secondInitValue = ByteArray(output, randomInt);
    free(output);

    int q = shaSize / 2 - std::log2(THREAD_COUNT);

    ByteArray firstThreadResult;
    ByteArray secondThreadResult;

    std::thread firstThread(StartIteration, firstInitValue, std::ref(firstThreadResult), shaSize, 1, q);
    std::thread secondThread(StartIteration, secondInitValue, std::ref(secondThreadResult), shaSize, 0, q);

    firstThread.join();
    secondThread.join();

    std::pair<ByteArray, ByteArray> collision;

    if (firstThreadResult.Size() != 0)
    {
        size_t d = std::abs(map[firstThreadResult].first - itersAndThread.first);
        if (map[firstThreadResult].second == itersAndThread.second)
        {
            collision = CalculateCollision(firstInitValue, firstInitValue, d, shaSize);
        }
        else
        {
            if (map[firstThreadResult].second == 1)
            {
                if (map[firstThreadResult].first <= itersAndThread.first)
                    collision = CalculateCollision(secondInitValue, firstInitValue, d, shaSize);
                else
                    collision = CalculateCollision(firstInitValue, secondInitValue, d, shaSize);
            }
            else
            {
                if (map[firstThreadResult].first <= itersAndThread.first)
                    collision = CalculateCollision(firstInitValue, secondInitValue, d, shaSize);
                else
                    collision = CalculateCollision(secondInitValue, firstInitValue, d, shaSize);
            }
        }
    }
    else if (secondThreadResult.Size() != 0)
    {
        size_t d = std::abs(map[secondThreadResult].first - itersAndThread.first);
        if (map[secondThreadResult].second == itersAndThread.second)
        {
            collision = CalculateCollision(secondInitValue, secondInitValue, d, shaSize);
        }
        else
        {
            if (map[secondThreadResult].second == 1)
            {
                if (map[secondThreadResult].first <= itersAndThread.first)
                    collision = CalculateCollision(secondInitValue, firstInitValue, d, shaSize);
                else
                    collision = CalculateCollision(firstInitValue, secondInitValue, d, shaSize);
            }
            else
            {
                if (map[secondThreadResult].first <= itersAndThread.first)
                    collision = CalculateCollision(firstInitValue, secondInitValue, d, shaSize);
                else
                    collision = CalculateCollision(secondInitValue, firstInitValue, d, shaSize);
            }
        }
    }

    //Output
    ByteArray hash = ShaXx(collision.first, shaSize);
    return collision;
}

int main()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::ofstream outputHash, outputData;

    outputHash.open(".\\birth_hash_out.txt", std::ios::out);
    outputData.open(".\\birth_mem_&_time.txt", std::ios::out);
    for (size_t j = FIRST_SHA_SIZE_VALUE; j < LAST_SHA_SIZE_VALUE; j++)
    {
        double summMemUsed = 0;
        double summTime = 0;
        std::vector<ByteArray> collisions;
        
        for (size_t i = 0; i < NUMBER_OF_COLLISIONS; i++)
        {
            bool isOk = false;
            do
            {
                start = std::chrono::system_clock::now();
                std::pair<ByteArray, ByteArray> collision = FindCollision(j);
                end = std::chrono::system_clock::now();

                if ((std::find(collisions.begin(), collisions.end(), collision.first) == collisions.end()
                     || std::find(collisions.begin(), collisions.end(), collision.second) == collisions.end())
                    && collision.first != collision.second)
                {
                    isOk = true;
                    collisions.push_back(collision.first);
                    collisions.push_back(collision.second);
                    ByteArray hash = ShaXx(collision.first, j);
                    outputHash << "x1: " << collision.first << std::endl << "x2: " << collision.second << std::endl;
                    outputHash << "SHA" << j << "(x): " << hash << std::endl;
                    outputHash << "-------------------------------------------------------------" << std::endl;
                }
            }
            while (!isOk);

            summTime += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / FLOAT_ONE_THOUSAND_CONST;
            summMemUsed += memUse;
        }
        
        outputData << j << ' ' << summTime / NUMBER_OF_COLLISIONS << ' ' << summMemUsed / NUMBER_OF_COLLISIONS << std::endl;
    }
    outputData.close();
    outputHash.close();

    outputHash.open(".\\rho_hash_out.txt", std::ios::out);
    outputData.open(".\\rho_mem_&_time.txt", std::ios::out);
    for (size_t j = FIRST_SHA_SIZE_VALUE; j < LAST_SHA_SIZE_VALUE; j++)
    {
        double summMemUsed = 0;
        double summTime = 0;
        std::vector<ByteArray> collisions;

        for (size_t i = 0; i < NUMBER_OF_COLLISIONS; i++)
        {
            bool isOk = false;
            do
            {
                start = std::chrono::system_clock::now();
                std::pair<ByteArray, ByteArray> collision = FindCollisionByRhoMethod(j);
                end = std::chrono::system_clock::now();

                if ((std::find(collisions.begin(), collisions.end(), collision.first) == collisions.end()
                    || std::find(collisions.begin(), collisions.end(), collision.second) == collisions.end())
                    && collision.first != collision.second)
                {
                    isOk = true;
                    collisions.push_back(collision.first);
                    collisions.push_back(collision.second);
                    ByteArray hash = ShaXx(collision.first, j);
                    outputHash << "x1: " << collision.first << std::endl << "x2: " << collision.second << std::endl;
                    outputHash << "SHA" << j << "(x): " << hash << std::endl;
                    outputHash << "-------------------------------------------------------------" << std::endl;
                }
            } while (!isOk);

            summTime += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / FLOAT_ONE_THOUSAND_CONST;
            summMemUsed += memUse;
        }

        outputData << j << ' ' << summTime / NUMBER_OF_COLLISIONS << ' ' << summMemUsed / NUMBER_OF_COLLISIONS << std::endl;
    }
    outputData.close();
    outputHash.close();

    return 0;
}
