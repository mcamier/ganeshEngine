#include "ghDoubleBufferedStackAllocator.h"

namespace ganeshEngine {

bool DoubleBufferedStackAllocator::initialize(void) {
    mBufferOne.initialize();
    mBufferTwo.initialize();
    mpCurrentBuffer = &mBufferOne;

    return mBufferOne.mIsInitialized && mBufferTwo.mIsInitialized;
}

void* DoubleBufferedStackAllocator::alloc(unsigned long byteSize) {
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
