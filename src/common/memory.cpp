#include "memory.hpp"

#include <cstdlib>
#include <cassert>

namespace rep
{
bool StackAllocator::initialize() {
    mpFirstAddr = malloc(mByteSize);
    if (!mpFirstAddr) return false;
    mpCurrentAddr = mpFirstAddr;
    mpLastAddr = (char *) mpFirstAddr + mByteSize;

    mIsInitialized = true;
    return mIsInitialized;
}


void *StackAllocator::alloc(unsigned long byteSize) {
    if (mIsInitialized) {
        if ((((char *) mpCurrentAddr) + byteSize) <= mpLastAddr) {
            mpCurrentAddr = (char *) mpCurrentAddr + byteSize;
            return mpCurrentAddr;
        }
        return nullptr;
    }
    return nullptr;
}

void StackAllocator::clear() {
    if (mIsInitialized) {
        mpCurrentAddr = mpFirstAddr;
    }
}


void StackAllocator::destroy() {
    // TODO implementation
    if (mIsInitialized) {
        free(mpFirstAddr);
    }
}


bool PoolAllocator::v_initialize() {
    uintptr_t nextPtrAddr;
    if (!mIsInitialized) {
        mpMemSection = malloc(mBlockAmount * (mBlockSize + sizeof(uintptr_t)));
    }
    assert(mpMemSection != nullptr);

    beginAddr = reinterpret_cast<uintptr_t>(mpMemSection);
    endAddr = beginAddr + mBlockAmount * (mBlockSize + sizeof(uintptr_t));

    mpFreePtr = mpMemSection;

    for (unsigned int i = 1; i < mBlockAmount; i++) {
        nextPtrAddr = beginAddr + (i * mBlockSize) + ((i - 1) * sizeof(uintptr_t));
        uintptr_t *ppp = reinterpret_cast<uintptr_t *>(nextPtrAddr);

        if (i == mBlockAmount - 1) {
            *ppp = 0;
        }
        else {
            *ppp = nextPtrAddr + sizeof(uintptr_t);
        }
    }

    mIsInitialized = true;
    return (mpMemSection != nullptr);
}

void *PoolAllocator::alloc() {
    if (mpFreePtr != nullptr) {
        void *candidate = mpFreePtr;
        uintptr_t *tempNextFreePtr = reinterpret_cast<uintptr_t *>(reinterpret_cast<uintptr_t>(candidate) +
                                                                   mBlockSize);
        void *nextPtr = reinterpret_cast<void *>(*tempNextFreePtr);
        mpFreePtr = nextPtr;
        uintptr_t candidateAsInteger = reinterpret_cast<uintptr_t>(candidate);
        assert((candidateAsInteger - beginAddr) % (mBlockSize + sizeof(uintptr_t)) == 0);

        return candidate;
    }
    return nullptr;
}

void PoolAllocator::free(void *mem) {
    uintptr_t test = reinterpret_cast<uintptr_t>(mem);
    //printf("free [%d]\n", test);
    assert(test >= beginAddr && test < endAddr);
    assert((test - beginAddr) % (mBlockSize + sizeof(uintptr_t)) == 0);

    void *temp = mpFreePtr;
    mpFreePtr = mem;
    uintptr_t *ppp = reinterpret_cast<uintptr_t *>(test + mBlockSize);
    *ppp = reinterpret_cast<uintptr_t>(temp);
}

void PoolAllocator::v_destroy() {
    free(mpMemSection);
}


bool DoubleBufferedStackAllocator::initialize(void) {
    mBufferOne.initialize();
    mBufferTwo.initialize();
    mpCurrentBuffer = &mBufferOne;

    return mBufferOne.mIsInitialized && mBufferTwo.mIsInitialized;
}

void *DoubleBufferedStackAllocator::alloc(unsigned long byteSize) {
    return mpCurrentBuffer->alloc(byteSize);
}

void DoubleBufferedStackAllocator::clear() {
    mpCurrentBuffer->clear();
}

void DoubleBufferedStackAllocator::swapBuffer() {
    mpCurrentBuffer = (mpCurrentBuffer == &mBufferOne) ? &mBufferTwo : &mBufferOne;
}

void DoubleBufferedStackAllocator::destroy() {
    mBufferOne.destroy();
    mBufferTwo.destroy();
}

}