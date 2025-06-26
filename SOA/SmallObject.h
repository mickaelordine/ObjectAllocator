//////////////////////////////////////////////
// SmallObject.h wrapper for a small object //
//////////////////////////////////////////////

#pragma once
#include <cstddef>
#include <corecrt_malloc.h>
#include "SmallObjectAllocator.h"
#include <threads.h>

#define DEFAULT_CHUNK_SIZE 4096 // 4kb is our fixed allocator's chunk size upper limit.
#define MAX_BLOCK_SIZE 64  // Maximum size of a block in bytes

template <std::size_t chunkSize = DEFAULT_CHUNK_SIZE,std::size_t maxSmallObjectSize = MAX_BLOCK_SIZE>
class SmallObject
{
public:
	virtual ~SmallObject() = default;

	static void* operator new(std::size_t size)
	{
		return SmallObjectAllocator::GetInstance().Allocate(size);
	}
	static void operator delete(void* p, std::size_t size) //here we use size to ensure the correct deallocation, to avoid memory overhead or time overhead looking for the correct size
	{
		SmallObjectAllocator::GetInstance().Deallocate(p, size); 
	}
	
};
