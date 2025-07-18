#include "MemoryManager.h"
#include <memory>
#include "SmallObjectAllocator.h"

MemoryManager::MemoryManager() 
: m_soa(SmallObjectAllocator::GetInstance())
{
}


void* MemoryManager::AllocateRaw(size_t size)
{
	return m_soa.GetInstance().Allocate(size);
}

void MemoryManager::DeallocateRaw(void* ptr, size_t size)
{
	m_soa.GetInstance().Deallocate(ptr, size);
}