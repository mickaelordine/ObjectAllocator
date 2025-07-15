#pragma once

#ifdef USE_MM_POWAAAA
inline void* operator new(std::size_t n) { return MM_MALLOC(n); }
inline void  operator delete(void* p) noexcept { MM_FREE(p); }
inline void* operator new[](std::size_t n) { return MM_MALLOC(n); }
inline void  operator delete[](void* p) noexcept { MM_FREE(p); }
#endif
