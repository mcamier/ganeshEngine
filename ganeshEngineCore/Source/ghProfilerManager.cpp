#include "ghProfilerManager.h"
#include "ghHeaders.h"

namespace ganeshEngine {

void ProfilerManager::update() {
    for(auto entry : mLastFrameSamplesMap) {
        auto globalEntry = mGlobalSamplesMap.find(entry.first);
        if(globalEntry == mGlobalSamplesMap.end()) {
            ProfilerGlobalEntry newGlobalSample{entry.first};
            newGlobalSample.mMinDurationMs = entry.second.mDurationMs;
            newGlobalSample.mMaxDurationMs = entry.second.mDurationMs;
            newGlobalSample.mAverageDurationMs = entry.second.mDurationMs;
            newGlobalSample.mSamplesAmount++;
            mGlobalSamplesMap.insert(make_pair(entry.first, newGlobalSample));
        } else {
            ProfilerGlobalEntry &global = globalEntry->second;
            global.mMinDurationMs = std::min(global.mMinDurationMs, entry.second.mDurationMs);
            global.mMaxDurationMs = std::max(global.mMaxDurationMs, entry.second.mDurationMs);
            global.mAverageDurationMs = ((global.mAverageDurationMs * global.mSamplesAmount) + entry.second.mDurationMs) / (global.mSamplesAmount+1);
            global.mSamplesAmount++;
        }
    }
    mLastFrameSamplesMap.clear();
}


void ProfilerManager::registerSample(std::string &name, F32 durationMs) {
    auto entry = mLastFrameSamplesMap.find(name);
    if(entry == mLastFrameSamplesMap.end()) {
        mLastFrameSamplesMap.insert(make_pair(name, ProfilerFrameEntry{name, durationMs}));
    } else {
        entry->second.mSampleAmount++;
        entry->second.mDurationMs += durationMs;
    }

}

void ProfilerManager::vDestroy() {
    _INFO("ProfilesManager details", LOG_CHANNEL::DEFAULT);
    for(auto entry : mGlobalSamplesMap) {
        _INFO("\t" << entry.first << " [avg : " << entry.second.mAverageDurationMs << "] [min : " << entry.second.mMinDurationMs << "] [max : " << entry.second.mMaxDurationMs << "]", LOG_CHANNEL::DEFAULT);
    }
}

ProfilerManager&(*gProfiler)() =  &ProfilerManager::get;
}
