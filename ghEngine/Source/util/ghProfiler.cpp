#include "util/ghProfiler.hpp"

#include "util/ghProfilerManager.hpp"

namespace ganeshEngine {

    AutoProfiler::AutoProfiler(const char *name) {
        mName = string(name);
        begin = high_resolution_clock::now();
    }

    AutoProfiler::~AutoProfiler() {
        auto dt = high_resolution_clock::now() - begin;
        gProfiler().registerSample(mName, (float) dt.count() / 1000000.0f);
    }
}