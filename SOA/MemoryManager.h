//////////////////////////////////////////////
//              MemoryManager.h             //
//////////////////////////////////////////////

#pragma once
#include "SmallObjectAllocator.h"
#include <utility> // per std::forward

class SmallObjectAllocator;


namespace MMA
{
    class MemoryManager
    {
    public:
        // Delete copy constructor and assignment operator to prevent copying
        MemoryManager(const MemoryManager&) = delete;
        MemoryManager();
        MemoryManager& operator=(const MemoryManager&) = delete;

        // Static method to access the singleton instance
        static MemoryManager& getInstance() { static MemoryManager s; return s; };

        void* AllocateRaw(size_t size);
        void  DeallocateRaw(void* ptr, size_t size);

    private:
        SmallObjectAllocator m_soa;
    };


    template<typename T, typename F>
    void MM_FREE(T* ptr, F size)
    {
        MMA::MemoryManager::getInstance().DeallocateRaw(ptr, size);
    }

    template<typename T>
    T* MM_NEW_ARR(std::size_t count)
    {
        if (count == 0) return nullptr;

        std::size_t totalSize = sizeof(T) * count + sizeof(std::size_t);
        void* p = MM_MALLOC(totalSize);
        *static_cast<std::size_t*>(p) = count;
        T* array = reinterpret_cast<T*>(static_cast<char*>(p) + sizeof(std::size_t));
        for (std::size_t i = 0; i < count; ++i)
        {
            new(array + i) T();
        }
        return array;
    }

    template<typename T, typename F>
    void MM_DELETE(T* ptr, F size)
    {
        MM_FREE(ptr, size);
    }

    template<typename T>
    void MM_DELETE(T* ptr)
    {
        MM_FREE(ptr, sizeof(T));
    }

    template<typename T>
    void MM_DELETE_ARR(T* ptr)
    {
        if (ptr)
        {
            char* basePtr = reinterpret_cast<char*>(ptr) - sizeof(std::size_t);
            std::size_t count = *reinterpret_cast<std::size_t*>(basePtr);
            for (std::size_t i = count; i > 0; --i)
            {
                ptr[i - 1].~T();
            }
            std::size_t totalSize = sizeof(T) * count + sizeof(std::size_t);
            MM_FREE(basePtr, totalSize);
        }
    }

    template<typename T>
    void* MM_MALLOC(T size)
    {
        return MMA::MemoryManager::getInstance().AllocateRaw(size);
    }

    template<typename T>
    T* MM_NEW()
    {
        void* memory = MM_MALLOC(sizeof(T));
        return new (memory) T();
    }

    template<typename T, typename... Args>
    T* MM_NEW(Args&&... args)
    {
        void* p = MM_MALLOC(sizeof(T));
        return new(p) T(std::forward<Args>(args)...);
    }

    template<typename T>
    void* MM_NEW(T size)
    {
        void* memory = MM_MALLOC((size_t) size);
        return new (memory) T();
    }
}