#pragma once
#include <cstdlib>
#include "MemoryManager.h"

#ifdef USE_MM_POWAAAA
void* operator new(std::size_t n) { return MMA::MM_MALLOC(n); }
void  operator delete(void* p, std::size_t size) noexcept { MMA::MM_FREE(p, size); }
void* operator new[](std::size_t n) { return MMA::MM_MALLOC(n); }
void  operator delete[](void* p, std::size_t size) noexcept { MMA::MM_DELETE(p, size); }
#endif