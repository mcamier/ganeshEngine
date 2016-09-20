#ifndef GANESHENGINE_GHPROFILERMANAGER_H
#define GANESHENGINE_GHPROFILERMANAGER_H

#include "ghHeaders.h"
#include "ghSystem.h"
#include "ghProfiler.h"

namespace ganeshEngine {

    using namespace std;


/**
 * Manager used to gather samples of profiled functions calls and
 * provides related datas for debugging purposes
 */
    class ProfilerManager : public System<ProfilerManager> {

    private:
        /**
         * Samples registered since the beginning of the current frame
         */
        map<string, ProfilerFrameEntry> mLastFrameSamplesMap;

        /**
         * All samples registered since the beginning of profiling, usually the
         * beginning of the game's execution
         */
        map<string, ProfilerGlobalEntry> mGlobalSamplesMap;

    public:
        /**
         * Update the manager, should be called every frames to register the samples
         * gathered during the current frame into global datas. Compute from pikes and
         * average for all sample category.
         */
        void update();

        /**
         * Register a sample
         *
         * @param name the name of the category the sample belongs to
         * @param durationMs the duration recorded in millisecond
         */
        void registerSample(std::string &name, F32 durationMs);

        /**
         * Destroy the profiler manager
         */
        void vDestroy();
    };

/**
 * Global access to profilerManager
 *
 * @return global reference to the profileManager singleton
 */
    extern ProfilerManager &(*gProfiler)();
}

#endif //GANESHENGINE_GHPROFILERMANAGER_H
