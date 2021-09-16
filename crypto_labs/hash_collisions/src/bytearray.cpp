#include "bytearray.h"

#include <sha.h>
#include <hex.h>
#include <iomanip>

ByteArray::ByteArray(std::string string) :
    m_storage(string.size())
{
    for (size_t i = 0; i < string.size(); ++i)
    {
        m_storage[i] = static_cast<byte>(string[i]);
    }
}

ByteArray::ByteArray(const byte* byteArrayPtr, size_t arraySize) :
    m_storage(arraySize)
{
    for (size_t i = 0; i < arraySize; ++i)
    {
        m_storage[i] = static_cast<byte>(byteArrayPtr[i]);
    }
}

ByteArray::ByteArray(const char* byteArrayPtr, size_t arraySize) :
    m_storage(arraySize)
{
    for (size_t i = 0; i < arraySize; ++i)
    {
        m_storage[i] = static_cast<byte>(byteArrayPtr[i]);
    }
}

const byte& ByteArray::operator[](const size_t index) const
{
    if (index >= m_storage.size())
        throw std::out_of_range("Index out of range\n");
    return m_storage[index];
}

byte& ByteArray::operator[](const size_t index)
{
    if (index >= m_storage.size())
        throw std::out_of_range("Index out of range\n");
    return m_storage[index];
}

std::_Vector_iterator<std::_Vector_val<std::_Simple_types<byte>>> ByteArray::Begin()
{
    return m_storage.begin();
}

std::_Vector_iterator<std::_Vector_val<std::_Simple_types<byte>>> ByteArray::End()
{
    return m_storage.end();
}

byte* ByteArray::Data()
{
    return m_storage.data();
}

size_t ByteArray::Size() const
{
    return m_storage.size();
}

void ByteArray::Erase(size_t first, size_t last)
{
    if (first > m_storage.size() || last > m_storage.size() || first > last)
        throw std::out_of_range("Error in interval range\n");
    m_storage.erase(m_storage.begin() + first, m_storage.begin() + last);
}

bool ByteArray::operator==(ByteArray& other) const
{
    if (Size() != other.Size())
        return false;
    for (size_t i = 0; i < Size(); i++)
    {
        if (m_storage[i] != other[i])
            return false;
    }

    return true;
}

bool ByteArray::operator<(const ByteArray& other) const
{
    if (Size() < other.Size())
        return true;
    for (size_t i = 0; i < Size(); i++)
    {
        if (m_storage[i] < other[i])
            return true;
        if (m_storage[i] > other[i])
            return false;
    }
    return false;
}

std::ofstream& operator<<(std::ofstream& out, ByteArray& byteArray)
{
    for (size_t i = 0; i < byteArray.Size(); ++i)
        out << std::hex << std::setfill('0') << std::setw(2) << (int)byteArray[i] << std::dec;
    return out;
}

std::ostream& operator<<(std::ostream& out, ByteArray& byteArray)
{
    for (size_t i = 0; i < byteArray.Size(); ++i)
        out << std::hex << std::setfill('0') << std::setw(2) << (int)byteArray[i] << std::dec;
    return out;
}

void ByteArray::Concatenation(ByteArray& other)
{
    m_storage.insert(End(), other.Begin(), other.End());
}