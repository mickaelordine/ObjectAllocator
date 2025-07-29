# ObjectAllocator - Custom Memory Manager in C++
## Scopo del progetto
Questo progetto implementa un sistema di Memory Management personalizzato in C++, seguendo l'implementazione di Alexandrescu nel suo libro Modern C++ Design, focalizzato sull’allocazione efficiente di oggetti piccoli (Small Object Allocation). Mira a sostituire l’allocazione standard (new/delete) con un sistema più performante, controllato e tracciabile.

## Architettura del sistema
- MemoryManager (Singleton)
Entry-point globale per ogni allocazione/deallocazione.

Espone le funzioni AllocateRaw(size) e DeallocateRaw(ptr, size).

- SmallObjectAllocator
Gestisce gli oggetti di dimensione inferiore a maxObjectSize.

Si occupa di smistare la richiesta all’allocatore corretto (FixedAllocator).

- FixedAllocator
Gestisce oggetti di dimensione fissa.

Divide la memoria in chunk e block per aumentare l’efficienza e minimizzare la frammentazione.

Riutilizza i blocchi liberati per nuove allocazioni.

- Chunk
Gestisce i blocchi

- Allocazioni grandi
Gli oggetti sopra maxObjectSize vengono allocati con malloc di sistema.

## Caratteristiche principali
- Override globale di new e delete.

- Allocazione efficiente per piccoli oggetti.

- Supporto per template helper MM_NEW e MM_DELETE.

## Come si usa?
Tramite define USE_MM_POWAAAA nel SOA.cpp overridando globalmente new e delete;
oppure
MMA::MM_NEW(sizeof(Class));
MMA::MM_DELETE(obj, sizeof(Class));

## Test e benchmarking
Puoi trovare un test base nel file SOA.cpp. Esegue un ciclo intensivo di allocazioni/deallocazioni per oggetti piccoli.

## Obiettivi futuri
- Aggiungere un BigObjectAllocator per gestire le allocazioni più grandi in modo più controllato.

## File principali
MemoryManager.h/.cpp – Singleton globale, entry point del sistema.

SmallObjectAllocator.h/.cpp – Smista le allocazioni agli allocator fissi.

FixedAllocator.h/.cpp – Gestione di chunk e blocchi a dimensione fissa.

Chunk.h/.cpp – Gestione dei blocchi all'interno dei Chunk.

SOA.cpp – Contiene i test di allocazione e deallocazione.