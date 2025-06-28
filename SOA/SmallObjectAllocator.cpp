/////////////////////////
// MY CLASSES INCLUDES //
/////////////////////////
#include "SmallObjectAllocator.h"

#include <cassert>

/***************************************************************************
params : chunkSize -> is the default chunk size (the length in bytes of each Chunk object), 
		 maxObjectSize -> is the maximum size of objects that must be considered to be "small."
SmallObjAllocator forwards requests for blocks larger than maxObjectSize directly to ::operator new. (todo: modify  it to make our BigObjAll)
This is usually a SINGLETON to be accessigble from anywhere in the program.
returns : SmallObjectAllocator object
***************************************************************************/
SmallObjectAllocator::SmallObjectAllocator(std::size_t chunkSize, std::size_t maxObjectSize) 
	: m_defaultChunkSize(chunkSize), m_maxObjectSize(maxObjectSize)
{
	m_pLastAlloc_ = m_pLastDealloc_ = nullptr;
}

SmallObjectAllocator& SmallObjectAllocator::GetInstance(std::size_t chunkSize, std::size_t maxObjectSize) 
{
	static SmallObjectAllocator instance(chunkSize, maxObjectSize); // Create a static instance of the SmallObjectAllocator, and we don't need to check if already exist because it is static
	return instance; 
}


/***************************************************************************
params : numBytes -> is the number of bytes to allocate.
returns : void* -> pointer to the allocated memory block.
***************************************************************************/
void* SmallObjectAllocator::Allocate(std::size_t numBytes) 
{
	if (numBytes > m_maxObjectSize) { return malloc(numBytes); } // Forward to global new operator for large objects, to substitute it with BigObjAllocator


	// check m_pLastAlloc_ to see if it is nullptr or if it has enough space to allocate the requested size
	if(m_pLastAlloc_ && m_pLastAlloc_->GetBlockSize() >= numBytes)
	{
		return m_pLastAlloc_->Allocate(); // Use the last allocator if it has enough space
	}

	// If m_pLastAlloc_ is nullptr or does not have enough space, create a new FixedAllocator
	FixedAllocator allocator(numBytes);
	m_pool_.push_back(allocator); // Store the allocator in the pool for future use
	m_pLastAlloc_ = &m_pool_.back(); // Set the last allocator to the newly created one
	return m_pLastAlloc_->Allocate();
}

/***************************************************************************
params : p -> is the pointer to the memory block to deallocate, 
		 size -> is the size of the object being deallocated.
returns : void -> no return value, the memory block is deallocated.
***************************************************************************/
void SmallObjectAllocator::Deallocate(void* ptr, std::size_t size) 
{
	// Check if the pointer is valid and if the size is within the limits
	assert(ptr != nullptr);
	assert(size <= m_maxObjectSize);
	assert(size > 0);

	// If the size is larger than the maximum object size, forward to global delete operator
	if (size > m_maxObjectSize) { free(ptr); return; }

	// check if m_pLastDealloc_ is not nullptr and if it has enough space to deallocate the requested size
	if (m_pLastDealloc_ && m_pLastDealloc_->GetBlockSize() == size) { m_pLastDealloc_->Deallocate(ptr); return; }

    //find the iterator for FixedAlloc
    auto it = std::find_if(m_pool_.begin(), m_pool_.end(),
        [this](const FixedAllocator& alloc) { return &alloc == m_pLastDealloc_; });

    //search in the previous sizes
    if (it != m_pool_.begin()) {
        auto prev = it - 1;
        if (prev->GetBlockSize() == size)
        {
            prev->Deallocate(ptr);
            m_pLastDealloc_ = &*prev;
            return;
        }
    }

    //search in the next sizes
    if (it != m_pool_.end()) {
        auto next = it + 1;
        if (next->GetBlockSize() == size)
        {
            next->Deallocate(ptr);
            m_pLastDealloc_ = &*next;
            return;
        }
    }

    // Otherwise search in all the pool
    for (auto& allocator : m_pool_) {
        if (allocator.GetBlockSize() == size) {
            allocator.Deallocate(ptr);
            m_pLastDealloc_ = &allocator;
            return;
        }
    }

    // Se siamo qui, qualcosa è andato storto
    assert(false && "Pointer not found in any allocator!");
}