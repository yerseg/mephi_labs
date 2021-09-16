#include "omac.h"
#include "helpers.h"

#define R_CONSTANT_128 0x87
#define MSB 128

namespace crypto
{

namespace mac
{

OmacProvider::OmacProvider() : m_blockSize(OMAC_BLOCK_SIZE)
{
}

void OmacProvider::SetKey(ByteArray key)
{
	m_key.Clear();
	m_currentBlock.Clear();

	m_key = key;
	m_additionalKeys = GenerateAdditionalKeys();
}

ByteArray OmacProvider::ComputeMac(ByteArray data)
{
	m_currentBlock.Clear();

	size_t blocksCount = data.Size() / m_blockSize;
	if (data.Size() % m_blockSize != 0)
		++blocksCount;

	for (size_t i = 0; i < blocksCount * m_blockSize; i += m_blockSize)
	{
		if (data.Size() - i >= m_blockSize)
			MacAddBlock(data.GetBlock(i, m_blockSize));
		else
			MacAddBlock(data.GetBlock(i, data.Size() - i));
	}

	return MacFinalize();
}

bool OmacProvider::VerifyMac(ByteArray data, ByteArray tag)
{
	if (ComputeMac(data) != tag)
		return false;
	return true;
}

void OmacProvider::MacAddBlock(ByteArray dataBlock)
{
	if (dataBlock.Size() > m_blockSize)
		throw std::runtime_error("BLOCK IS SO BIG!");

	if (dataBlock.Size() < m_blockSize)
		m_isPadded = true;

	if (m_currentBlock.Size() == 0)
	{
		m_currentBlock = dataBlock;
	}
	else
	{
		m_currentBlock = helpers::AesBlockEncrypt(m_key, m_currentBlock, helpers::padding_type::MAC);
		helpers::XorByteArray(dataBlock, m_currentBlock);
		m_currentBlock = dataBlock;
	}
}

ByteArray OmacProvider::MacFinalize()
{
	if (m_isPadded)
	{
		helpers::XorByteArray(m_currentBlock, m_additionalKeys.second);
		return helpers::AesBlockEncrypt(m_key, m_currentBlock, helpers::padding_type::MAC);
	}

	helpers::XorByteArray(m_currentBlock, m_additionalKeys.first);

	return helpers::AesBlockEncrypt(m_key, m_currentBlock, helpers::padding_type::MAC);
}

std::pair<ByteArray, ByteArray> OmacProvider::GenerateAdditionalKeys() const
{
	byte zeroBuffer[OMAC_BLOCK_SIZE] = { 0x00 };
	ByteArray zero = ByteArray(zeroBuffer, OMAC_BLOCK_SIZE);
	ByteArray l = helpers::AesBlockEncrypt(m_key, zero, helpers::padding_type::MAC);

	std::pair<ByteArray, ByteArray> keys;

	helpers::LeftBitShift(l, 1);

	if (l[l.Size() - 1] & MSB == 0)
	{
		keys.first = l;
	}
	else
	{
		zeroBuffer[OMAC_BLOCK_SIZE - 1] = R_CONSTANT_128;
		const ByteArray constant = ByteArray(zeroBuffer, OMAC_BLOCK_SIZE);
		helpers::XorByteArray(l, constant);
		keys.first = l;
	}

	ByteArray temp = keys.first;
	helpers::LeftBitShift(temp, 1);

	if (keys.first[keys.first.Size() - 1] & MSB == 0)
	{
		keys.second = temp;
	}
	else
	{
		zeroBuffer[OMAC_BLOCK_SIZE - 1] = R_CONSTANT_128;
		const ByteArray constant = ByteArray(zeroBuffer, OMAC_BLOCK_SIZE);
		helpers::XorByteArray(temp, constant);
		keys.second = temp;
	}

	return keys;
}

}
}

