#ifndef GANESHENGINE_STACKALLOCATOR_H
#define GANESHENGINE_STACKALLOCATOR_H

#include <iostream>

namespace ganeshEngine {

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

}

#endif