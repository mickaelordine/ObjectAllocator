#include "FixedAllocator.h"
#include <cassert>
#include <iostream>


FixedAllocator::FixedAllocator(std::size_t blockSize)
    : m_blockSize_(blockSize)
{
	//assert(m_blockSize_ > 0);

	// set m_blockSize_
	std::size_t numBlocks = DEFAULT_CHUNK_SIZE / m_blockSize_;
    if (numBlocks > MAX_SMALL_OBJECT_SIZE)
    { 
        numBlocks = MAX_SMALL_OBJECT_SIZE;
    }

    // set m_numBlocks_ value
	m_numBlocks_ = static_cast<unsigned char>(numBlocks);
    //assert(m_numBlocks_ == numBlocks); //truncation check

    m_allocChunk_ = m_deallocChunk_ = nullptr;
}

/***************************************************************************
- explanation : this function allocate a chunk of memory in two ways, if allocChunk is free, we can return it in O(1) time, 
otherwise we will search for a free chunk in the chunks_ vector, if we can't find one, we will create a new chunk and return it. O(n) in the worst case.
- params : 
- returns : the address of the allocated memory block
***************************************************************************/
void* FixedAllocator::Allocate() 
{
    if (m_allocChunk_ == nullptr || m_allocChunk_->blocksAvailable_ == 0)
    {
        // No available memory in this chunk, Try to find one
        auto s = std::find_if(m_chunks_.begin(), m_chunks_.end(),
			[this](const Chunk& c) { return &c == m_allocChunk_; });

        for (;; ++s)
        {
            if (s == m_chunks_.end())
            {
                if (reserve == 0)
                {
                    reserve = 100;
                    m_chunks_.reserve(m_chunks_.size() + reserve);
                }
                --reserve;
                Chunk newChunk;
                newChunk.Init(m_blockSize_, m_numBlocks_);
                m_chunks_.push_back(newChunk);
                m_allocChunk_ = &m_chunks_.back();
                m_deallocChunk_ = &m_chunks_.back();
                break;
            }
            if (s->blocksAvailable_ > 0)
            {
                // Found a chunk 
                m_allocChunk_ = &*s;
				m_deallocChunk_ = &*s; //added this to avoid access violation when deallocating, if the m_chunks get reallocated we follow the new point in the memory
                break;
            }
        }
    }
    /*assert(m_allocChunk_ != 0);
    assert(m_allocChunk_->blocksAvailable_ > 0);*/
    return m_allocChunk_->Allocate(m_blockSize_);

}

/***************************************************************************
- explanation : this function deallocate a memBlock of a Chunk, to do that it start searching in the last deallocated chunk, then we check around the m_deallocPtr, 
otherwise it will search in the chunks_ vector.
- params : the pointer to the memory block to be deallocated, the ptr is a block address inside a chunk, so we need to find the chunk that contains this block and deallocate it.
- returns : void
***************************************************************************/
void FixedAllocator::Deallocate(void* ptr) 
{
	//assert(ptr != nullptr);
	//create the corrects pointers to point at the first and last address of the chunk and start searching lower and upper cases around the last deallocation
    const std::size_t chunkLength = m_numBlocks_ * m_blockSize_;

	// start with deallocChunk_ if it is not null
    if (m_deallocChunk_ && (ptr >= m_deallocChunk_->pData_ && ptr <= m_deallocChunk_->pData_ + m_blockSize_ * m_numBlocks_))
    {
        m_deallocChunk_->Deallocate(ptr, m_blockSize_);
        DoDeallocate(ptr);
        return;
    }
    
    // Trova l'iteratore corrente corrispondente a m_deallocChunk_
    auto it = std::find_if(m_chunks_.begin(), m_chunks_.end(),
        [this](const Chunk& c) { return &c == m_deallocChunk_; });

    auto next = it;
	auto prev = it;

    for (;;)
    {
        if (next != m_chunks_.end())
        {
            // Check next chunk
            next = next + 1;
            if (next != m_chunks_.end() &&
                ptr >= next->pData_ &&
                ptr < next->pData_ + m_blockSize_ * m_numBlocks_)
            {
                next->Deallocate(ptr, m_blockSize_);
                m_deallocChunk_ = &*next;
                DoDeallocate(ptr);
                return;
            }
        }

        // Check previous chunk
        if (prev != m_chunks_.begin())
        {
            prev = prev - 1;
            if (ptr >= prev->pData_ &&
                ptr < prev->pData_ + m_blockSize_ * m_numBlocks_)
            {
                prev->Deallocate(ptr, m_blockSize_);
                m_deallocChunk_ = &*prev;
                DoDeallocate(ptr);
                return;
            }
        }
    }
    assert(0);
    return;
}

/***************************************************************************
- explanation : this function check if there is at least 2 chunks complete free, if so it will release the last one, if not, swap the deallocChunk_ with the last chunk in the vector so we can check if there is at least 2 chunks free
- params : the pointer to the memory block to be deallocated, the ptr is a block address inside a chunk, so we need to find the chunk that contains this block and deallocate it.
- returns : void
***************************************************************************/
void FixedAllocator::DoDeallocate(void* ptr) 
{
    // call into the chunk, will adjust the inner list but won't release memory
    //m_deallocChunk_->Deallocate(ptr, m_blockSize_);

    if (m_deallocChunk_->blocksAvailable_ == m_numBlocks_)
    {
        // deallocChunk_ is completely free, should we release it? 

        Chunk& lastChunk = m_chunks_.back();

        if (&lastChunk == m_deallocChunk_)
        {
            // check if we have two last chunks empty

            if (m_chunks_.size() > 1 &&
                m_deallocChunk_->blocksAvailable_ == m_numBlocks_)
            {
                // Two free chunks, discard the last one
                lastChunk.Release();
                m_chunks_.pop_back();
                m_allocChunk_ = m_deallocChunk_ = &m_chunks_.front();
            }
            return;
        }

        if (lastChunk.blocksAvailable_ == m_numBlocks_)
        {
            // Two free blocks, discard one
            lastChunk.Release();
            m_chunks_.pop_back();
            m_allocChunk_ = m_deallocChunk_;
        }
        else
        {
            // move the empty chunk to the end
            std::swap(*m_deallocChunk_, lastChunk);
            m_allocChunk_ = &m_chunks_.back();
        }
    }
    return;
}
