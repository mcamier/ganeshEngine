#ifndef GANESHENGINE_GHPROFILER_H
#define GANESHENGINE_GHPROFILER_H

#include <chrono>
#include <string>

#include "ghTypes.hpp"

#ifdef PROFILING_ENABLED
#define PROFILE(name, op) { \
        { \
        AutoProfiler profiler(name); \
        op; \
        } \
    }
#else
#define PROFILE(name, op) { \
        op;\
    }
#endif

namespace ganeshEngine {

using namespace std;
using namespace std::chrono;

/** Profiler class, its constructor will retrieve current time from the system
*  and it's destructor will get current time again
*
*/
class AutoProfiler {
private:
    string mName;
    high_resolution_clock::time_point begin;
    high_resolution_clock::duration dt{0};

public:
    AutoProfiler(const char *name);

    AutoProfiler(const AutoProfiler &) = delete;

    AutoProfiler &operator=(const AutoProfiler &) = delete;

    ~AutoProfiler();
};


/**
*
*/
struct ProfilerFrameEntry {
    string mName;
    U8 mSampleAmount;
    F32 mDurationMs;

    ProfilerFrameEntry(string &name) :
            mName(name),
            mSampleAmount(0),
            mDurationMs(0) {}

    ProfilerFrameEntry(string &name, F32 durationMs) :
            mName(name),
            mSampleAmount(1),
            mDurationMs(durationMs) {}
};


/**
*
*/
struct ProfilerGlobalEntry {
    string mName;
    F32 mMinDurationMs;
    F32 mMaxDurationMs;
    F32 mAverageDurationMs;
    U32 mSamplesAmount;

    ProfilerGlobalEntry(string name) :
            mName(name),
            mMinDurationMs(0.0f),
            mMaxDurationMs(0.0f),
            mAverageDurationMs(0.0f),
            mSamplesAmount(0) {}

};

}

#endif //GANESHENGINE_GHPROFILER_H
