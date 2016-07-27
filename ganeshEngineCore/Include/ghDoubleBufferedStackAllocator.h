#ifndef GANESHENGINE_DOUBLEBUFFEREDSTACKALLOCATOR_H
#define GANESHENGINE_DOUBLEBUFFEREDSTACKALLOCATOR_H

#include "ghStackAllocator.h"

namespace ganeshEngine {

    class DoubleBufferedStackAllocator {

    private:
        StackAllocator *mpCurrentBuffer;
        StackAllocator mBufferOne;
        StackAllocator mBufferTwo;

    public:
        DoubleBufferedStackAllocator(unsigned long byteSize) :
                mBufferOne(byteSize),
                mBufferTwo(byteSize),
                mpCurrentBuffer(&mBufferOne) {}

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

#endif //GANESHENGINE_DOUBLEBUFFEREDSTACKALLOCATOR_H
