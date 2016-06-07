#ifndef GANESHENGINE_POOLALLOCATOR_H
#define GANESHENGINE_POOLALLOCATOR_H

#include "ghHeaders.h"

namespace ganeshEngine {

class PoolAllocator {

private:
    uintptr_t beginAddr;
    uintptr_t endAddr;

    void* mpFreePtr {nullptr};
    void* mpMemSection {nullptr};
    bool mIsInitialized {false};

    size_t mBlockSize;
    size_t mBlockAmount;

public:
    PoolAllocator(size_t blockSize, size_t blockAmount) :
            mBlockSize(blockSize),
            mBlockAmount(blockAmount) {}

    bool v_initialize(void);
    void v_destroy(void);

    void *alloc(void);
    void free(void*);
    bool isInitialized(void) { return mIsInitialized; }
};
}

#endif //GANESHENGINE_POOLALLOCATOR_H
