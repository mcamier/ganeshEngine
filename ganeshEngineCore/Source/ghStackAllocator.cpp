#include "ghStackAllocator.h"

namespace ganeshEngine {

bool StackAllocator::initialize() {
    mpFirstAddr = malloc(mByteSize);
    if (!mpFirstAddr) return false;
    mpCurrentAddr = mpFirstAddr;
    mpLastAddr = (char*)mpFirstAddr + mByteSize;

    mIsInitialized = true;
    return mIsInitialized;
}


void* StackAllocator::alloc(unsigned long byteSize) {
    if (mIsInitialized) {
        if ((((char*)mpCurrentAddr) + byteSize) <= mpLastAddr) {
            mpCurrentAddr = (char*)mpCurrentAddr + byteSize;
            return mpCurrentAddr;
        }
        _WARNING("Allocator runs out of memory, please clear it to alloc again", LOG_CHANNEL::DEFAULT);
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
    //TODO implement destroy method
    _TRACE("start DESTROY StackAllocator", LOG_CHANNEL::DEFAULT);
    if (mIsInitialized) {
        free(mpFirstAddr);
    }
    _TRACE("end DESTROY StackAllocator", LOG_CHANNEL::DEFAULT);
}

}