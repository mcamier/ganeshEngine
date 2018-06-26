#ifndef GE_MEMORY_H
#define GE_MEMORY_H

#include <iostream>
#include <cstdint>
#include <cstddef>

namespace ge {
namespace utils {

class StackAllocator {
    friend class DoubleBufferedStackAllocator;

private:
    unsigned long mByteSize;
    bool mIsInitialized;

    void *mpFirstAddr;
    void *mpLastAddr;
    void *mpCurrentAddr;

    StackAllocator &operator=(const StackAllocator &);

    StackAllocator(const StackAllocator &);

public:
    StackAllocator(unsigned long byteSize) :
            mByteSize(byteSize),
            mIsInitialized(false),
            mpFirstAddr(nullptr),
            mpLastAddr(nullptr),
            mpCurrentAddr(nullptr) {}

    bool initialize(void);

    void destroy(void);

    void *alloc(unsigned long byteSize);

    void clear(void);

    template<typename T>
    T *alloc() {
        if (mIsInitialized) {
            if ((((char *) mpCurrentAddr) + sizeof(T)) < mpLastAddr) {
                mpCurrentAddr = (char *) mpCurrentAddr + sizeof(T);
                return new(mpCurrentAddr)T;
            }
            return nullptr;
        }
        return nullptr;
    }
};


class PoolAllocator {

private:
    uintptr_t beginAddr;
    uintptr_t endAddr;

    void *mpFreePtr{nullptr};
    void *mpMemSection{nullptr};
    bool mIsInitialized{false};

    size_t mBlockSize;
    size_t mBlockAmount;

public:
    PoolAllocator(size_t blockSize, size_t blockAmount) :
            mBlockSize(blockSize),
            mBlockAmount(blockAmount) {}

    bool v_initialize(void);

    void v_destroy(void);

    void *alloc(void);

    void free(void *);

    bool isInitialized(void) { return mIsInitialized; }
};


class DoubleBufferedStackAllocator {

private:
    StackAllocator *mpCurrentBuffer;
    StackAllocator mBufferOne;
    StackAllocator mBufferTwo;

public:
    DoubleBufferedStackAllocator(unsigned long byteSize) :
            mpCurrentBuffer(&mBufferOne),
            mBufferOne(byteSize),
            mBufferTwo(byteSize) {}

    DoubleBufferedStackAllocator &operator=(const DoubleBufferedStackAllocator &) = delete;

    DoubleBufferedStackAllocator(const DoubleBufferedStackAllocator &) = delete;

    bool initialize(void);

    void destroy(void);

    void swapBuffer(void);

    void *alloc(unsigned long byteSize);

    void clear(void);

    template<typename T>
    T *alloc() {
        return mpCurrentBuffer->alloc<T>();
    }
};

}
}

#endif //GE_MEMORY_H
