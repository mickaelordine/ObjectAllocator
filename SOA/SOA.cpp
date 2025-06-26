// SOA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>
#include <chrono>

#define AMOUNT_OF_ALLOCATION 4096

// MyClass.h
#include "SmallObject.h"

// Classe che usa l'allocatore ottimizzato
class MySmallClass : public SmallObject<> 
{
private:
    int data[10];

public:
    MySmallClass() = default;
    void doSomething() { }
};

class MyNormalClass
{
private:
    int data[10];

public:
    MyNormalClass() = default;
    void doSomething() { /* logica */ }
};




int main()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
	//NORMAL ALLOCATOR USAGE EXAMPLE
	std::vector<MyNormalClass*> normal_Objects;
    // Usa allocatore standard (se disabilitato con #define)
    for (int i = 0; i < AMOUNT_OF_ALLOCATION; ++i) {
        normal_Objects.push_back(new MyNormalClass());
    }  
    
    // Cleanup
    for (auto* obj : normal_Objects) {
        delete obj;  // Deallocazione ottimizzata automatica
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference in Normal Allocation = " << std::chrono::duration_cast<std::chrono::nanoseconds>((end - begin) / 1000).count() << "[ns]" << std::endl;


    
    std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
	//SMALL OBJECT ALLOCATOR USAGE EXAMPLE
    std::vector<MySmallClass*> small_Objects;
    for (int i = 0; i < AMOUNT_OF_ALLOCATION; ++i) {
        small_Objects.push_back(new MySmallClass());
    }

    
    
    // Cleanup
    for (auto* obj : small_Objects) {
        delete obj;  // Deallocazione ottimizzata automatica
    }

    std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
    std::cout << "Time difference in smallObject Allocation = " << std::chrono::duration_cast<std::chrono::nanoseconds>((end1 - begin1) / 1000).count() << "[ns]" << std::endl;


    return 0;
}
