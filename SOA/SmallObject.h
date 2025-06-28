//////////////////////////////////////////////
// SmallObject.h wrapper for a small object //
//////////////////////////////////////////////

#pragma once
#include <cstddef>
#include <corecrt_malloc.h>
#include "SmallObjectAllocator.h"
#include <threads.h>

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
