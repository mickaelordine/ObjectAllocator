// SOA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


// MyClass.h
#include "SmallObject.h"

// Classe che usa l'allocatore ottimizzato
class MySmallClass : public SmallObject<> 
{
private:
    int data[10];

public:
    MySmallClass() { }
    void doSomething() { }
};

// Uso personalizzato con parametri specifici
class MyCustomClass : public SmallObject<8192,128>
{
private:
    char buffer[100];

public:
    MyCustomClass() {}
};

// La stessa identica sintassi, ma usa ::operator new standard
class MyNormalClass : public SmallObject<0,0>
{
private:
    int data[10];

public:
    MyNormalClass() { /* costruttore */ }
    void doSomething() { /* logica */ }
};

int main()
{
    // Usa small allocator (se abilitato)
    MySmallClass* obj1 = new MySmallClass();
    delete obj1;

    // Usa allocatore standard (se disabilitato con #define)
    MyNormalClass* obj2 = new MyNormalClass();
    delete obj2;

    // Array di oggetti
    std::vector<MySmallClass*> objects;
    for (int i = 0; i < 1000; ++i) {
        objects.push_back(new MySmallClass());
    }

    // Cleanup
    for (auto* obj : objects) {
        delete obj;  // Deallocazione ottimizzata automatica
    }

    return 0;
}
