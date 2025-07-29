// SOA.cpp : This file contains the 'main' function. Program execution begins and ends there.



#include <iostream>
#include <time.h>
#include <chrono>
#include <iomanip>

//#define USE_MM_POWAAAA
#define AMOUNT_OF_ALLOCATION 10000000

// MyClass.h
#include "MM_GlobalOverride.h"
#include "MemoryManager.h"
#include "SystemAllocator.h"


class MyNormalClass
{
private:
    int a;
    int b;
    int c;
    

public:
    MyNormalClass() = default;
    void doSomething() { /* logica */ }
};

class MyNormalClassChar
{
private:
    char a;
    char b;
    char c;


public:
    MyNormalClassChar() = default;
    void doSomething() { /* logica */ }
};

class MySmallClassInt
{
private:
    int a;
    int b;
    int c;

public:
    MySmallClassInt() = default;
    void doSomething() { /* logica */ }
};

class MySmallClassChar
{
private:
    char a;
    char b;
    char c;

public:
    MySmallClassChar() = default;
    void doSomething() { /* logica */ }
};

//TEST METHODS
void BulkAllocationExample()
{
    //BULK ALLOCATION
    //NORMAL ALLOCATOR USAGE EXAMPLE
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::vector <MyNormalClass*, SystemAllocator<MyNormalClass*>> normal_Objects;
    // Usa allocatore standard (se disabilitato con #define)
    for (int i = 0; i < AMOUNT_OF_ALLOCATION; ++i) {
        normal_Objects.push_back(new MyNormalClass());
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto duration = (end - begin);
    std::chrono::duration<double> seconds = duration; // conversione implicita

    std::cout << "Time in STDNormalObjectInt Allocation = "
        << std::fixed << std::setprecision(3) // stampa con 3 decimali
        << seconds.count() << "[s]" << std::endl;

    begin = std::chrono::steady_clock::now();
    // Cleanup
    for (auto* obj : normal_Objects) {
        delete obj;
    }

    end = std::chrono::steady_clock::now();
    duration = (end - begin);
    seconds = duration; // conversione implicita

    std::cout << "Time in STDNormalObjectInt Dealloc = "
        << std::fixed << std::setprecision(3) // stampa con 3 decimali
        << seconds.count() << "[s]" << std::endl;

    normal_Objects.clear(); // Clear the vector to release memory

    begin = std::chrono::steady_clock::now();

    std::vector<MyNormalClassChar*, SystemAllocator<MyNormalClassChar*>> normal_ObjectsChar;
    for (int i = 0; i < AMOUNT_OF_ALLOCATION; ++i) {
        normal_ObjectsChar.push_back(new MyNormalClassChar());
    }

    end = std::chrono::steady_clock::now();
    duration = (end - begin);
    seconds = duration; // conversione implicita

    std::cout << "Time in STDNormalObjChar Alloc = "
        << std::fixed << std::setprecision(3) // stampa con 3 decimali
        << seconds.count() << "[s]" << std::endl;
    begin = std::chrono::steady_clock::now();
    // Cleanup
    for (auto* obj : normal_ObjectsChar) {
        delete obj;  // Deallocazione ottimizzata automatica
    }
    normal_ObjectsChar.clear(); // Clear the vector to release memory
    
    end = std::chrono::steady_clock::now();
    duration = (end - begin);
    seconds = duration; // conversione implicita

    std::cout << "Time in STDNormalObjectInt Dealloc = "
        << std::fixed << std::setprecision(3) // stampa con 3 decimali
        << seconds.count() << "[s]" << std::endl;
    std::cout << "\n\n";


    ////SMALL OBJECT ALLOCATOR USAGE EXAMPLE
    begin = std::chrono::steady_clock::now();

    std::vector<MySmallClassInt*, SystemAllocator<MySmallClassInt*>> small_ObjectsInt;
    for (int i = 0; i < AMOUNT_OF_ALLOCATION; ++i) {
        small_ObjectsInt.push_back((MySmallClassInt*)MMA::MM_NEW(sizeof(MySmallClassInt)));
    }

    end = std::chrono::steady_clock::now();
    duration = (end - begin);
    seconds = duration; // conversione implicita

    std::cout << "Time in MySmallObjInt Alloc = "
        << std::fixed << std::setprecision(3) // stampa con 3 decimali
        << seconds.count() << "[s]" << std::endl;

    begin = std::chrono::steady_clock::now();
    // Cleanup
    for (auto* obj : small_ObjectsInt) {
        MMA::MM_DELETE(obj, sizeof(MySmallClassInt));
    }
    small_ObjectsInt.clear(); // Clear the vector to release memory

    end = std::chrono::steady_clock::now();
    duration = (end - begin);
    seconds = duration; // conversione implicita

    std::cout << "Time in MySmallObjInt Dealloc = "
        << std::fixed << std::setprecision(3) // stampa con 3 decimali
        << seconds.count() << "[s]" << std::endl;


    //SMALL OBJECT ALLOCATOR USAGE EXAMPLE
    begin = std::chrono::steady_clock::now();

    std::vector<MySmallClassChar*, SystemAllocator<MySmallClassChar*>> small_ObjectsChar;
    for (int i = 0; i < AMOUNT_OF_ALLOCATION; ++i) {
        small_ObjectsChar.push_back((MySmallClassChar*)MMA::MM_NEW(sizeof(MySmallClassChar)));
    }

    end = std::chrono::steady_clock::now();
    duration = (end - begin);
    seconds = duration; // conversione implicita

    std::cout << "Time in MySmallObjChar Alloc = "
        << std::fixed << std::setprecision(3) // stampa con 3 decimali
        << seconds.count() << "[s]" << std::endl;
    begin = std::chrono::steady_clock::now();
    // Cleanup
    for (auto* obj : small_ObjectsChar) {
        MMA::MM_DELETE(obj, sizeof(MySmallClassChar));
    }

    end = std::chrono::steady_clock::now();
    duration = (end - begin);
    seconds = duration; // conversione implicita

    std::cout << "Time in MySmallObjChar Dealloc = "
        << std::fixed << std::setprecision(3) // stampa con 3 decimali
        << seconds.count() << "[s]" << std::endl;
    std::cout << "\n\n";
}

void NoBulkAllocationExample()
{
    //NOBULK ALLOCATION
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int i = 0; i < AMOUNT_OF_ALLOCATION; ++i)
    {
        auto* obj = new MyNormalClass();
        delete obj;
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto duration = (end - begin);
    std::chrono::duration<double> seconds = duration;

    std::cout << "Time in STDNormalObjectInt Alloc+Dealloc = "
        << std::fixed << std::setprecision(3)
        << seconds.count() << "[s]" << std::endl;
    //SMALL OBJECT ALLOCATOR USAGE EXAMPLE
    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < AMOUNT_OF_ALLOCATION; ++i)
    {
        auto* obj = MMA::MM_NEW(sizeof(MySmallClassInt));
        MMA::MM_DELETE(obj, sizeof(MySmallClassInt));
    }

    end = std::chrono::steady_clock::now();
    duration = (end - begin);
    seconds = duration;

    std::cout << "Time in MySmallObjectInt Alloc+Dealloc = "
        << std::fixed << std::setprecision(3)
        << seconds.count() << "[s]" << std::endl;
}

//MAIN FUNCTION
int main()
{
	BulkAllocationExample();
    std::cout << "\n";
	NoBulkAllocationExample();
    return 0;
}