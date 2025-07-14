// SOA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>
#include <chrono>
#include <iomanip>


#define AMOUNT_OF_ALLOCATION 5000000 //10M allocations

// MyClass.h
#include "SmallObject.h"

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

class MySmallClassInt : public SmallObject
{
private:
    int a;
    int b;
    int c;

public:
    MySmallClassInt() = default;
    void doSomething() { }
};


class MySmallClassChar : public SmallObject
{
private:
    char a;
    char b;
    char c;

public:
    MySmallClassChar() = default;
    void doSomething() {}
};


//TEST METHODS
void BulkAllocationExample()
{
    //BULK ALLOCATION
    //NORMAL ALLOCATOR USAGE EXAMPLE
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::vector<MyNormalClass*> normal_Objects;
    // Usa allocatore standard (se disabilitato con #define)
    for (int i = 0; i < AMOUNT_OF_ALLOCATION; ++i) {
        normal_Objects.push_back(new MyNormalClass());
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto duration = (end - begin);
    std::chrono::duration<double> seconds = duration; // conversione implicita

    std::cout << "Time in NormalObjectInt Allocation = "
        << std::fixed << std::setprecision(3) // stampa con 3 decimali
        << seconds.count() << "[s]" << std::endl;


    begin = std::chrono::steady_clock::now();
    // Cleanup
    for (auto* obj : normal_Objects) {
        delete obj;  // Deallocazione ottimizzata automatica
    }

    end = std::chrono::steady_clock::now();
    duration = (end - begin);
    seconds = duration; // conversione implicita

    std::cout << "Time in NormalObjectInt Dealloc = "
        << std::fixed << std::setprecision(3) // stampa con 3 decimali
        << seconds.count() << "[s]" << std::endl;

    normal_Objects.clear(); // Clear the vector to release memory

    begin = std::chrono::steady_clock::now();

    std::vector<MyNormalClassChar*> normal_ObjectsChar;
    for (int i = 0; i < AMOUNT_OF_ALLOCATION; ++i) {
        normal_ObjectsChar.push_back(new MyNormalClassChar());
    }

    end = std::chrono::steady_clock::now();
    duration = (end - begin);
    seconds = duration; // conversione implicita

    std::cout << "Time in NormalObjChar Alloc = "
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

    std::cout << "Time in NormalObjectInt Dealloc = "
        << std::fixed << std::setprecision(3) // stampa con 3 decimali
        << seconds.count() << "[s]" << std::endl;
    std::cout << "\n\n";


    //SMALL OBJECT ALLOCATOR USAGE EXAMPLE
    begin = std::chrono::steady_clock::now();

    std::vector<MySmallClassInt*> small_ObjectsInt;
    for (int i = 0; i < AMOUNT_OF_ALLOCATION; ++i) {
        small_ObjectsInt.push_back(new MySmallClassInt());
    }

    end = std::chrono::steady_clock::now();
    duration = (end - begin);
    seconds = duration; // conversione implicita

    std::cout << "Time in SmallObjInt Alloc = "
        << std::fixed << std::setprecision(3) // stampa con 3 decimali
        << seconds.count() << "[s]" << std::endl;
    begin = std::chrono::steady_clock::now();
    // Cleanup
    for (auto* obj : small_ObjectsInt) {
        delete obj;  // Deallocazione ottimizzata automatica
    }
    small_ObjectsInt.clear(); // Clear the vector to release memory

    end = std::chrono::steady_clock::now();
    duration = (end - begin);
    seconds = duration; // conversione implicita

    std::cout << "Time in SmallObjInt Dealloc = "
        << std::fixed << std::setprecision(3) // stampa con 3 decimali
        << seconds.count() << "[s]" << std::endl;
    //SMALL OBJECT ALLOCATOR USAGE EXAMPLE
    begin = std::chrono::steady_clock::now();

    std::vector<MySmallClassChar*> small_ObjectsChar;
    for (int i = 0; i < AMOUNT_OF_ALLOCATION; ++i) {
        small_ObjectsChar.push_back(new MySmallClassChar());
    }

    end = std::chrono::steady_clock::now();
    duration = (end - begin);
    seconds = duration; // conversione implicita

    std::cout << "Time in SmallObjChar Alloc = "
        << std::fixed << std::setprecision(3) // stampa con 3 decimali
        << seconds.count() << "[s]" << std::endl;
    begin = std::chrono::steady_clock::now();
    // Cleanup
    for (auto* obj : small_ObjectsChar) {
        delete obj;  // Deallocazione ottimizzata automatica
    }

    end = std::chrono::steady_clock::now();
    duration = (end - begin);
    seconds = duration; // conversione implicita

    std::cout << "Time in SmallObjChar Dealloc = "
        << std::fixed << std::setprecision(3) // stampa con 3 decimali
        << seconds.count() << "[s]" << std::endl;
    std::cout << "\n\n";
}

void NoBulkAllocationExample()
{
    //NOBULK ALLOCATION
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    // Usa allocatore standard (se disabilitato con #define)
    for (int i = 0; i < AMOUNT_OF_ALLOCATION; ++i)
    {
        auto* obj = new MyNormalClass();
        delete obj;  // Deallocazione ottimizzata automatica
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto duration = (end - begin);
    std::chrono::duration<double> seconds = duration; // conversione implicita

    std::cout << "Time in NormalObjectInt Alloc+Dealloc = "
        << std::fixed << std::setprecision(3) // stampa con 3 decimali
        << seconds.count() << "[s]" << std::endl;
    //SMALL OBJECT ALLOCATOR USAGE EXAMPLE
    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < AMOUNT_OF_ALLOCATION; ++i)
    {
        auto* obj = new MySmallClassInt();
        delete obj;
    }

    end = std::chrono::steady_clock::now();
    duration = (end - begin);
    seconds = duration; // conversione implicita

    std::cout << "Time in SmallObjectInt Alloc+Dealloc = "
        << std::fixed << std::setprecision(3) // stampa con 3 decimali
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