#include "Chunk.h"
#include <cassert>

/***************************************************************************
params : blockSize -> the size of each block in the chunk
		 blocks -> the number of blocks in the chunk
returns : void
***************************************************************************/
void Chunk::Init(std::size_t blockSize, unsigned char blocks)
{
    pData_ = new unsigned char[blockSize * blocks];
    firstAvailableBlock_ = 0;
    blocksAvailable_ = blocks;
    unsigned char i = 0;
    unsigned char* p = pData_;

	// Initialize the blocks with their indices
    for (; i != blocks; p += blockSize)
    {
        *p = ++i;
    }

}

// COST: the allocation cost is O(1), the only things is that with chunk we use more memory at the first beginning
/**************************************************************************
params : blockSize -> the size of each block in the chunk

returns : the address of the first available block in the chunk, or 0 if no blocks are available
***************************************************************************/
void* Chunk::Allocate(std::size_t blockSize)
{
    if (!blocksAvailable_)
        return 0;

	unsigned char* pResult = pData_ + (firstAvailableBlock_ * blockSize); //basic pointer arithmetic to get the address of the first available block

    // Update firstAvailableBlock_ to point to the next block
    firstAvailableBlock_ = *pResult;
    --blocksAvailable_;

    return pResult;
}

/***************************************************************************
params : blockSize -> the size of each block in the chunk
		 p -> the address of the block we want to deallocate
returns : void, the block is deallocated and added to the available blocks in the chunk
***************************************************************************/
void Chunk::Deallocate(void* p, std::size_t blockSize)
{
	assert(p >= pData_);
    unsigned char* toRelease = static_cast<unsigned char*>(p);
    // Alignment check 
    assert((toRelease - pData_) % blockSize == 0);
    *toRelease = firstAvailableBlock_;
    firstAvailableBlock_ = static_cast<unsigned char>(
        (toRelease - pData_) / blockSize);
    // Truncation check 
    assert(firstAvailableBlock_ ==
        (toRelease - pData_) / blockSize);
    ++blocksAvailable_;
}



