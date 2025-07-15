#pragma once
#include <type_traits>
#include <new>
#include "MemoryManager.h"

#define MM_NEW(Type, ...) \
    new (MemoryManager::getInstance().AllocateRaw(sizeof(Type))) Type(__VA_ARGS__)

#define MM_DELETE(ptr, size)                          \
    do {                                              \
        if (ptr) {                                    \
            auto* _p = (ptr);                         \
            using _T = std::remove_pointer_t<decltype(_p)>; \
            _p->~_T();                                \
            MemoryManager::getInstance().DeallocateRaw(_p, size);   \
        }                                             \
    } while (0)

#define MM_MALLOC(size)       MemoryManager::getInstance.AllocateRaw(size)
#define MM_FREE(ptr)          MemoryManager::getInstance.DeallocateRaw(ptr, size)