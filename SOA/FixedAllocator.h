//////////////////////////////////////////////
//              FixedAllocator.h            //
//////////////////////////////////////////////

#pragma once
#include <cstddef>
#include <vector>
#include "Chunk.h"
#include "SystemAllocator.h"


#define DEFAULT_CHUNK_SIZE 4096 //8192 //4096 //2048 // 4kb is our fixed allocator's chunk size upper limit.
#define MAX_SMALL_OBJECT_SIZE 255 //128 //255 //64 // Maximum size of a block in bytes

// Forward declaration of Chunk class
struct Chunk;

class FixedAllocator
{
public:
    FixedAllocator(std::size_t blockSize);
	~FixedAllocator() = default;
    void* Allocate();
    void Deallocate(void* ptr);
	void DoDeallocate(void* ptr);

public:
    std::size_t GetBlockSize() const { return m_blockSize_; }


private:
	// blockSize and NumBlocks are used to define the size of each chunk and the number of chunks, we need to allocate and move inside them
    std::size_t m_blockSize_;   //Size di ogni blocco
    unsigned char m_numBlocks_; //Numero di blocchi per chunk
    
    typedef std::vector<Chunk, SystemAllocator<Chunk>> Chunks; //Un vettore di Chunk che usiamo per tenere dinamicamente la dimensione dei chunk aggiornata nello Heap.
    Chunks m_chunks_;
    Chunk* m_allocChunk_; /*To achieve a speedy lookup, FixedAllocator does not iterate through chunks_ looking for a space for each allocation.
                        Instead, it holds a pointer to the last chunk that was used for an allocation(allocChunk_).
                        Whenever an allocation request comes, FixedAllocator::Allocate first checks allocChunk_ for available space. 
                        If allocChunk_ has a slot available, the allocation request is satisfied using allocChunk_. 
                        If not, a linear search occurs(and, possibly, a new Chunk is appended to the chunks_ vector). 
                        In any case, allocChunk_ is updated to point to that found or added chunk.*/
	Chunk* m_deallocChunk_; //deallocChunk che ci dice l'indirizzo dell'ultimo chunk deallocato.

    int reserve = 0;


};

