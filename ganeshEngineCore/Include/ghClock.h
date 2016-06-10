#ifndef GANESHENGINE_GHCLOCK_H
#define GANESHENGINE_GHCLOCK_H

#include "ghCore.h"

namespace ganeshEngine {

class Clock {
private:

	/**
	 * Total nanoseconds elapsed
	 */
    U64 mTotalNanoSeconds;

	/**
	 * Define how time elapsed
	 * Value of 1.0f will let time elapsed normally
	 * Value of 2.0f will make things happens two times quicker
	 * Value of 0.5f will make things happens two times lower
	 */
    F32 mScale;

	/**
	 * True will stop the time counting
	 */
    bool mIsPaused;

public:
    Clock(U64 baseTimeNanoSeconds = 0) : mScale(1.0f), mIsPaused(true), mTotalNanoSeconds(baseTimeNanoSeconds) {}
    Clock(const Clock&) = delete;
    Clock& operator=(const Clock&) = delete;
    ~Clock() {}

    /**
     * One tick update
     *
     * @param dtNanoSecond amount of time to append to the clock's total elapsed time
     */
    void tick(U32 dtNanoSecond);

    /**
     * One fixed time step update
     *
     * @param force True will force the stop to be took even if the clock is paused
     */
    void singleStep(bool force);

    /**
     * Getter of pause status
     *
     * @return True if the clock is paused, false otherwise
     */
    bool isPaused();

    /**
     * Setter of pause status
     *
     * @param value True to pause the clock, false otherwise
     */
    void setPause(bool value);
};

}

#endif //GANESHENGINE_GHCLOCK_H
