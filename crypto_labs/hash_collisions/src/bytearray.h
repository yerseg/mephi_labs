#ifndef __BYTEARRAY_H__
#define __BYTEARRAY_H__

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using byte = unsigned char;
using ByteArrayStorage = std::vector<byte>;

class ByteArray
{
public:
    ByteArray(std::string string);
    ByteArray(const byte* byteArrayPtr, size_t arraySize);
    ByteArray(const char* byteArrayPtr, size_t arraySize);
    ByteArray() = default;

    const byte& operator[](const size_t index) const;
    byte& operator[](const size_t index);
    bool operator==(ByteArray& other) const;
    bool operator<(const ByteArray& other) const;

    friend std::ofstream& operator<<(std::ofstream& out, ByteArray& byteArray);
    friend std::ostream& operator<<(std::ostream& out, ByteArray& byteArray);

    std::_Vector_iterator<std::_Vector_val<std::_Simple_types<byte>>> Begin();
    std::_Vector_iterator<std::_Vector_val<std::_Simple_types<byte>>> End();
    byte* Data();
    size_t Size() const;
    void Erase(size_t first, size_t last);
    void Concatenation(ByteArray& other);

private:
    ByteArrayStorage m_storage;
};

#endif //__BYTEARRAY_H__
