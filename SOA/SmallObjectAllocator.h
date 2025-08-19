//////////////////////////////////////////////
//          SmallObjectAllocator.h          //
//////////////////////////////////////////////

#pragma once
#include <cstddef>
#include <deque>
#include <map>
#include "FixedAllocator.h"
class SmallObjectAllocator
{
public:
    SmallObjectAllocator(std::size_t chunkSize,std::size_t maxObjectSize);
	~SmallObjectAllocator() = default;
    void* Allocate(std::size_t numBytes);
	void Deallocate(void* p, std::size_t size); //the interesting thing here is that we pass a s param the size of the object to deallocate, the standard free() doesn't do that

private:
	std::vector<FixedAllocator, SystemAllocator<FixedAllocator>> m_pool_; //pool of fixed allocators
	FixedAllocator* m_pLastAlloc_; //last fixed used for allocation
	FixedAllocator* m_pLastDealloc_; //last fixed used for deallocation
	std::size_t m_defaultChunkSize, m_maxObjectSize;
};

