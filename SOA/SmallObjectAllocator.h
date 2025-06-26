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
	static SmallObjectAllocator& GetInstance(std::size_t chunkSize = 4096, std::size_t maxObjectSize = 128); //singleton instance of the allocator, we can pass the chunk size and max object size to the constructor
    void* Allocate(std::size_t numBytes);
	void Deallocate(void* p, std::size_t size); //the interesting thing here is that we pass a s param the size of the object to deallocate, the standard free() doesn't do that
	
	enum class AllocatorSize //range in bytes for the fixed allocators in the pool from 0 to 64 bytes, each fixed allocator is responsible for a range of sizes
	{
		SuperSmall = 4, //4 bytes
		Small = 8, //8 bytes
		Medium = 16, //16 bytes
		Large = 32, //32 bytes
		ExtraLarge = 64, //64 bytes
		ExtraHuge = 128, //128 bytes
		End = 256 //256 bytes, this is the end of the range, we don't use this size
	};

private:
	std::vector<FixedAllocator> m_pool_; //pool of fixed allocators
	FixedAllocator* m_pLastAlloc_; //last fixed used for allocation
	FixedAllocator* m_pLastDealloc_; //last fixed used for deallocation
	std::size_t m_defaultChunkSize, m_maxObjectSize;
	/*std::map<std::size_t, std::size_t> map;*/
	
};

