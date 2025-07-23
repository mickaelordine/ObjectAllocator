#include "MemoryManager.h"
#include <memory>
#include "SmallObjectAllocator.h"

MMA::MemoryManager::MemoryManager() 
	: m_soa(SmallObjectAllocator::GetInstance())
{
}


void* MMA::MemoryManager::AllocateRaw(std::size_t size)
{
	return m_soa.GetInstance().Allocate(size);
}

void MMA::MemoryManager::DeallocateRaw(void* ptr, std::size_t size)
{
	m_soa.GetInstance().Deallocate(ptr, size);
}