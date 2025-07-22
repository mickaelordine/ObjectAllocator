#pragma once

template<typename T>
class SystemAllocator
{
public:
    using value_type = T;

    SystemAllocator() = default;
    template<typename U> SystemAllocator(const SystemAllocator<U>&)
    {
    }

    T* allocate(std::size_t n)
    {
        return static_cast<T*>(std::malloc(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t)
    {
        std::free(p);
    }
};