#pragma once
#include <cstdlib>
#include "MemoryManager.h"

#ifndef USE_MM_POWAAAA
void* operator new(std::size_t n) { return MMA::MM_NEW(n); }
void  operator delete(void* p, std::size_t size) noexcept { MMA::MM_DELETE(p, size); }
void* operator new[](std::size_t type, int count) { return MMA::MM_NEW_ARR(type, count); }
void  operator delete[](void* p, std::size_t size) noexcept { MMA::MM_DELETE_ARR(p); }
#endif