#ifndef RENDERENGINEPLAYGROUND_PROFILER_HPP
#define RENDERENGINEPLAYGROUND_PROFILER_HPP

#include <map>
#include <chrono>
#include <string>
#include <iostream>

#include "managers.hpp"

#ifdef PROFILING_ENABLED
#define BEGIN_PROFILING(name) \
        {\
            AutoProfiler profiler(name);
#define END_PROFILING \
    }
#else
#define BEGIN_PROFILING(name)
#define END_PROFILING
#endif

namespace rep
{

using std::chrono::high_resolution_clock;

// Profiler class, its constructor will retrieve current time from the system and it's destructor will get current
// time again
// Using this class implies the ProfilerManager is already started
// Example:
//      ...
//      {
//          AutoProfiler profiler("VulkanContextManager update");
//          VulkanContextManager::get().vUpdate();
//      }
//      ...
// Because AutoProfiler is a RAII class, once the execution leave the scope where the autoprofile was created, it will
// be destroyed, but during its destruction the ProfilerManager will notified with the timing sample

class AutoProfiler
{
private:
    std::string mName;
    high_resolution_clock::time_point begin;
    high_resolution_clock::duration dt{0};

public:
    AutoProfiler(const char *name);

    AutoProfiler(const AutoProfiler &) = delete;

    AutoProfiler &operator=(const AutoProfiler &) = delete;

    ~AutoProfiler();
};


// Store a unique profiling sample
struct ProfilerFrameEntry
{
    uint16_t sampleAmount = 0;
    float durationMs = 0;

    ProfilerFrameEntry(float durationMs) :
            sampleAmount(1),
            durationMs(durationMs)
    {}
};


// Store the agregated timing sampled for a given named sampler
struct ProfilerGlobalEntry
{
    float minDurationMs;
    float maxDurationMs;
    uint32_t samplesAmount;
    double totalDurationMs;

    ProfilerGlobalEntry() :
            minDurationMs(.0f),
            maxDurationMs(.0f),
            totalDurationMs(.0f),
            samplesAmount(0)
    {}

    double getAverageDurationMs() {
        return this->totalDurationMs / (double)this->samplesAmount;
    }
};


// ProfilerManagerInitializeArgs_t gathers all properties that could be giving to the ProfilerManager during its
// initialization in order to customize its behavior
struct ProfilerManagerInitializeArgs_t
{
};


// ProfilerManager is responsible for profiling samples
//
// It's a singleton manager and should be accessed via get method
// Example:
//      ProfilerManager::get().registerSample("Frame preparation", 256);
class ProfilerManager :
        public SingletonManager<ProfilerManager, ProfilerManagerInitializeArgs_t>
{
    friend SingletonManager<ProfilerManager, ProfilerManagerInitializeArgs_t>;

private:
    // Samples registered since the beginning of the current frame
    std::map<std::string, ProfilerFrameEntry> lastFrameSamplesMap;

    // All samples registered since the beginning of profiling, usually the beginning of the game's execution
    std::map<std::string, ProfilerGlobalEntry> globalSamplesMap;

    ProfilerManager() = default;

    ProfilerManager(const ProfilerManager &) = delete;

    ProfilerManager &operator=(const ProfilerManager &) = delete;

    void vInit(ProfilerManagerInitializeArgs_t args) override {}

    void vDestroy() override;

public:
    // Update the manager, should be called every frames to register the samples gathered during the current frame
    // into global datas. Compute from pikes and average for all sample category.
    void vUpdate() override;

    // Register a sample
    // param name : the name of the category the sample belongs to
    // param durationMs : the duration recorded in millisecond
    void registerSample(std::string &name, float durationMs);

};

}

#endif //RENDERENGINEPLAYGROUND_PROFILER_HPP