//////////////////////////////////////////////
//          SmallObjectAllocator.h          //
//////////////////////////////////////////////

#pragma once
#include <cstddef>
#include <map>
#include "FixedAllocator.h"
class SmallObjectAllocator
{
public:
    SmallObjectAllocator(std::size_t chunkSize,std::size_t maxObjectSize);
	~SmallObjectAllocator() = default;
	static SmallObjectAllocator& GetInstance(std::size_t chunkSize = 4096, std::size_t maxObjectSize = 64); //singleton instance of the allocator, we can pass the chunk size and max object size to the constructor
    void* Allocate(std::size_t numBytes);
	void Deallocate(void* p, std::size_t size); //the interesting thing here is that we pass a s param the size of the object to deallocate, the standard free() doesn't do that

private:
	std::vector<FixedAllocator> m_pool_; //pool of fixed allocators
	FixedAllocator* m_pLastAlloc_; //last fixed used for allocation
	FixedAllocator* m_pLastDealloc_; //last fixed used for deallocation
	std::size_t m_defaultChunkSize, m_maxObjectSize;
	/*std::map<std::size_t, std::size_t> map;*/
	
};

