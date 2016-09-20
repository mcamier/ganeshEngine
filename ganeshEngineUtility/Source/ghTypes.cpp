#include <iostream>
#include "ghTypes.h"

namespace ganeshEngine {

void gAssertFailure(const char *expr, const char *file, U32 line) {
	std::cerr << expr << " failed in (" << file << ") at line " << line << std::endl;
}

U32 gRandr(unsigned int min, unsigned int max) {
	double scaled = (double) rand() / RAND_MAX;
	return (max - min + 1) * scaled + min;
}

U32 gGetNextId() {
	static U32 lastId = 0;
	return ++lastId;
}

}