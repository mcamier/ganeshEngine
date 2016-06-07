#ifndef GANESHENGINE_STACKALLOCATOR_H
#define GANESHENGINE_STACKALLOCATOR_H

#include "ghHeaders.h"
#include <iostream>
#include <gtest/gtest_prod.h>

namespace ganeshEngine {

class StackAllocator {
    friend class DoubleBufferedStackAllocator;
    FRIEND_TEST(MemoryTest, allocationArea);

private:
    unsigned long mByteSize;
    bool mIsInitialized;

    void* mpFirstAddr;
    void* mpLastAddr;
    void* mpCurrentAddr;

    StackAllocator & operator=(const StackAllocator &);
    StackAllocator(const StackAllocator &);

public:
    StackAllocator(unsigned long byteSize) :
            mByteSize(byteSize),
            mIsInitialized(false),
            mpCurrentAddr(nullptr),
            mpLastAddr(nullptr),
            mpFirstAddr(nullptr) {}

    bool initialize(void);
    void destroy(void);
    void* alloc(unsigned long byteSize);
    void clear(void);

    template <typename T>
    T* alloc() {
        if (mIsInitialized) {

            if ((((char*)mpCurrentAddr) + sizeof(T)) < mpLastAddr) {
                mpCurrentAddr = (char*)mpCurrentAddr + sizeof(T);
                return new (mpCurrentAddr)T;
            }
            _WARNING("Stack allocator runs out of memory, please clear it to alloc again");
            return nullptr;
        }
        return nullptr;
    }
};
}

#endif