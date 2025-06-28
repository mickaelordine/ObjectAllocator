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


// Classe che usa l'allocatore ottimizzato
class MySmallClass : public SmallObject
{
private:
    int data[10];
    /*char data[8];*/

public:
    MySmallClass() = default;
    void doSomething() { }
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
    std::cout << "Time in NormalObject Allocation = " << std::chrono::duration_cast<std::chrono::nanoseconds>((end - begin) / 1000).count() << "[ns]" << std::endl;

	begin = std::chrono::steady_clock::now();
    // Cleanup
    for (auto* obj : normal_Objects) {
        delete obj;  // Deallocazione ottimizzata automatica
    }

	end = std::chrono::steady_clock::now();
	std::cout << "Time in NormalObject Deallocation = " << std::chrono::duration_cast<std::chrono::nanoseconds>((end - begin) / 1000).count() << "[ns]" << std::endl;
    


    //SMALL OBJECT ALLOCATOR USAGE EXAMPLE
    begin = std::chrono::steady_clock::now();

    std::vector<MySmallClass*> small_Objects;
    for (int i = 0; i < AMOUNT_OF_ALLOCATION; ++i) {
        small_Objects.push_back(new MySmallClass());
    }

    end = std::chrono::steady_clock::now();
    std::cout << "Time in smallObject Allocation = " << std::chrono::duration_cast<std::chrono::nanoseconds>((end - begin) / 1000).count() << "[ns]" << std::endl;

    begin = std::chrono::steady_clock::now();
    // Cleanup
    for (auto* obj : small_Objects) {
        delete obj;  // Deallocazione ottimizzata automatica
    }

    end = std::chrono::steady_clock::now();
    std::cout << "Time in smallObject Deallocation = " << std::chrono::duration_cast<std::chrono::nanoseconds>((end - begin) / 1000).count() << "[ns]" << std::endl;

    return 0;
}



/*
RIPRENDI DA qui:
! abbiamo appena aggiustato il deallocator del fixed ed è migliorato drasticamente
- ora bisogna vedere se è possibile  migliorare l'allocazione, adesso quello che manca controllare sono i chunk nella fase di deallocazione e allocazione.

*/