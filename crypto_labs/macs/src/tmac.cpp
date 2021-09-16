#include "tmac.h"
#include "helpers.h"

#define TMAC_OUTPUT_BLOCK_SIZE 8

namespace crypto
{

namespace mac
{

TruncatedMacProvider::TruncatedMacProvider() : m_blockSize(TMAC_BLOCK_SIZE)
{
}

void TruncatedMacProvider::SetKey(ByteArray key)
{
	m_key.Clear();
	m_currentBlock.Clear();

	m_key = key;
}

ByteArray TruncatedMacProvider::ComputeMac(ByteArray data)
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

bool TruncatedMacProvider::VerifyMac(ByteArray data, ByteArray tag)
{
	if (ComputeMac(data) != tag)
		return false;
	return true;
}

void TruncatedMacProvider::MacAddBlock(ByteArray dataBlock)
{
	if (dataBlock.Size() > m_blockSize)
		throw std::runtime_error("BLOCK IS SO BIG!");

	if (m_currentBlock.Size() == 0)
	{
		byte zeroBuffer[TMAC_BLOCK_SIZE] = { 0x00 };
		m_currentBlock = dataBlock;
		helpers::XorByteArray(m_currentBlock, ByteArray(zeroBuffer, TMAC_BLOCK_SIZE));
	}
	else
	{
		m_currentBlock = helpers::AesBlockEncrypt(m_key, m_currentBlock, helpers::padding_type::PKCS7);
		helpers::XorByteArray(dataBlock, m_currentBlock);
		m_currentBlock = dataBlock;
	}
}

ByteArray TruncatedMacProvider::MacFinalize()
{
	return helpers::AesBlockEncrypt(m_key, m_currentBlock, helpers::padding_type::PKCS7).GetBlock(0, TMAC_OUTPUT_BLOCK_SIZE);
}

}
}

