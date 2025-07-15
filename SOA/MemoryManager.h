#pragma once
#include "SmallObjectAllocator.h"

class MemoryManager
{
public:
    // Delete copy constructor and assignment operator to prevent copying
	MemoryManager(const MemoryManager&) = delete;
    MemoryManager& operator=(const MemoryManager&) = delete;

    // Static method to access the singleton instance
    inline static MemoryManager& getInstance() { static MemoryManager s; return s; }

    void* AllocateRaw(size_t size);
    void  DeallocateRaw(void* ptr, size_t size);

    template<typename T, typename... Args>
    T* AllocateObject(Args&&... args) {
            
    }

    template<typename T>
    void DeallocateObject(T* ptr) {
            
    }


private:
    MemoryManager();
	SmallObjectAllocator m_soa;
};

