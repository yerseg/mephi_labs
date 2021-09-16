#include "helpers.h"
#include "hmac.h"

#define OPAD 0x5c
#define IPAD 0x36

namespace crypto
{

namespace mac
{

HmacProvider::HmacProvider() : m_blockSize(HMAC_BLOCK_SIZE)
{
}

void HmacProvider::SetKey(ByteArray key)
{
    m_key.Clear();
    m_currentBlock.Clear();

    m_key = key;
	ByteArray k = m_key;

	for (size_t i = 0; i < k.Size(); ++i)
	{
		k[i] ^= IPAD;
	}

	UpdateSha256(k);
}

ByteArray HmacProvider::ComputeMac(ByteArray data)
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

bool HmacProvider::VerifyMac(ByteArray data, ByteArray tag)
{
	if (ComputeMac(data) != tag)
		return false;
	return true;
}

void HmacProvider::MacAddBlock(ByteArray dataBlock)
{
	UpdateSha256(dataBlock);
}

ByteArray HmacProvider::MacFinalize()
{
	ByteArray temp = FinalSha256();
	ByteArray k = m_key;

	for (size_t i = 0; i < k.Size(); ++i)
	{
		k[i] ^= OPAD;
	}

	UpdateSha256(k);
	UpdateSha256(temp);

	return FinalSha256();
}

void HmacProvider::UpdateSha256(ByteArray dataBlock)
{
	m_shaObj.Update(dataBlock.Data(), dataBlock.Size());
}

ByteArray HmacProvider::FinalSha256()
{
    byte digest[CryptoPP::SHA256::DIGESTSIZE];
    m_shaObj.Final(digest);
    return ByteArray(digest, CryptoPP::SHA256::DIGESTSIZE);
}

}
}
