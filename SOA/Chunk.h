//////////////////////////////////////////////
//					Chunk.h                 //
//////////////////////////////////////////////

#pragma once
#include <cstddef>

struct Chunk
{
	void Init(std::size_t blockSize, unsigned char blocks); // TOTSIZE = blockSize * blocks
	void* Allocate(std::size_t blockSize); //our malloc()
	void Deallocate(void* ptr, std::size_t blockSize); //our free()
	void Release(); //relelase memory allocated in pData_

	unsigned char* pData_; //� il buffer allocato che contiene tutti i blocchi di memoria gestiti da questo chunk.
	unsigned char firstAvailableBlock_; //which hold  the index of the first avaible block in the chunck
	unsigned char blocksAvailable_; // the number of blocks avaible
};

