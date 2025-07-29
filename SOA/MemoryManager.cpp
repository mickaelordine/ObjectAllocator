#include "MemoryManager.h"
#include <memory>
#include "SmallObjectAllocator.h"

MMA::MemoryManager::MemoryManager() 
	: m_soa(DEFAULT_CHUNK_SIZE, MAX_SMALL_OBJECT_SIZE)
{
}


void* MMA::MemoryManager::AllocateRaw(std::size_t size)
{
	return m_soa.Allocate(size);
}

void MMA::MemoryManager::DeallocateRaw(void* ptr, std::size_t size)
{
	m_soa.Deallocate(ptr, size);
}