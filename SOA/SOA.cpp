// SOA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>
#include <chrono>

#define AMOUNT_OF_ALLOCATION 500000 //500k allocations

// MyClass.h
#include "SmallObject.h"

class MyNormalClass
{
private:
    int data[10];
    //char data[8];

public:
    MyNormalClass() = default;
    void doSomething() { /* logica */ }
};

class MyNormalClassChar
{
private:
    char data[10];

public:
    MyNormalClassChar() = default;
    void doSomething() { /* logica */ }
};


// Classe che usa l'allocatore ottimizzato
class MySmallClassInt : public SmallObject
{
private:
    int data[10];

public:
    MySmallClassInt() = default;
    void doSomething() { }
};



// Classe che usa l'allocatore ottimizzato
class MySmallClassChar : public SmallObject
{
private:
    char data[10];

public:
    MySmallClassChar() = default;
    void doSomething() {}
};








int main()
{
    //NORMAL ALLOCATOR USAGE EXAMPLE
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	
	std::vector<MyNormalClass*> normal_Objects;
    // Usa allocatore standard (se disabilitato con #define)
    for (int i = 0; i < AMOUNT_OF_ALLOCATION; ++i) {
        normal_Objects.push_back(new MyNormalClass());
    }  
    
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time in NormalObjectInt Allocation = " << std::chrono::duration_cast<std::chrono::nanoseconds>((end - begin) / 1000).count() << "[ns]" << std::endl;

	begin = std::chrono::steady_clock::now();
    // Cleanup
    for (auto* obj : normal_Objects) {
        delete obj;  // Deallocazione ottimizzata automatica
    }

	end = std::chrono::steady_clock::now();
	std::cout << "Time in NormalObjectInt Deallocation = " << std::chrono::duration_cast<std::chrono::nanoseconds>((end - begin) / 1000).count() << "[ns]" << std::endl;
    

	normal_Objects.clear(); // Clear the vector to release memory

    begin = std::chrono::steady_clock::now();

    std::vector<MyNormalClassChar*> normal_ObjectsChar;
    for (int i = 0; i < AMOUNT_OF_ALLOCATION; ++i) {
        normal_ObjectsChar.push_back(new MyNormalClassChar());
    }

    end = std::chrono::steady_clock::now();
    std::cout << "Time in NormalObjChar Allocation = " << std::chrono::duration_cast<std::chrono::nanoseconds>((end - begin) / 1000).count() << "[ns]" << std::endl;

    begin = std::chrono::steady_clock::now();
    // Cleanup
    for (auto* obj : normal_ObjectsChar) {
        delete obj;  // Deallocazione ottimizzata automatica
    }
    normal_ObjectsChar.clear(); // Clear the vector to release memory

    end = std::chrono::steady_clock::now();
    std::cout << "Time in NormalObjChar Deallocation = " << std::chrono::duration_cast<std::chrono::nanoseconds>((end - begin) / 1000).count() << "[ns]" << std::endl;



    //SMALL OBJECT ALLOCATOR USAGE EXAMPLE
    begin = std::chrono::steady_clock::now();

    std::vector<MySmallClassInt*> small_ObjectsInt;
    for (int i = 0; i < AMOUNT_OF_ALLOCATION; ++i) {
        small_ObjectsInt.push_back(new MySmallClassInt());
    }

    end = std::chrono::steady_clock::now();
    std::cout << "Time in smallObjectInt Allocation = " << std::chrono::duration_cast<std::chrono::nanoseconds>((end - begin) / 1000).count() << "[ns]" << std::endl;

    begin = std::chrono::steady_clock::now();
    // Cleanup
    for (auto* obj : small_ObjectsInt) {
        delete obj;  // Deallocazione ottimizzata automatica
    }
	small_ObjectsInt.clear(); // Clear the vector to release memory

    end = std::chrono::steady_clock::now();
    std::cout << "Time in smallObjectInt Deallocation = " << std::chrono::duration_cast<std::chrono::nanoseconds>((end - begin) / 1000).count() << "[ns]" << std::endl;

    //SMALL OBJECT ALLOCATOR USAGE EXAMPLE
    begin = std::chrono::steady_clock::now();

    std::vector<MySmallClassChar*> small_ObjectsChar;
    for (int i = 0; i < AMOUNT_OF_ALLOCATION; ++i) {
        small_ObjectsChar.push_back(new MySmallClassChar());
    }

    end = std::chrono::steady_clock::now();
    std::cout << "Time in smallObjectChar Allocation = " << std::chrono::duration_cast<std::chrono::nanoseconds>((end - begin) / 1000).count() << "[ns]" << std::endl;

    begin = std::chrono::steady_clock::now();
    // Cleanup
    for (auto* obj : small_ObjectsChar) {
        delete obj;  // Deallocazione ottimizzata automatica
    }

    end = std::chrono::steady_clock::now();
    std::cout << "Time in smallObjectChar Deallocation = " << std::chrono::duration_cast<std::chrono::nanoseconds>((end - begin) / 1000).count() << "[ns]" << std::endl;

    return 0;
}