#include <memory/ghStackAllocator.hpp>

namespace ganeshEngine {

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

}