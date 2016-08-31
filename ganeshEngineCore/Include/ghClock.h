#ifndef GANESHENGINE_GHCLOCK_H
#define GANESHENGINE_GHCLOCK_H

#include "ghCore.h"

namespace ganeshEngine {

class Clock {
private:

	/** Total nanoseconds elapsed
	 */
	U64 mTotalNanoSeconds;

	/**
	 */
	U32 mLastTimeAdded;

	/** Define how time elapsed
	 * Value of 1.0f will let time elapsed normally
	 * Value of 2.0f will make things happens two times quicker
	 * Value of 0.5f will make things happens two times lower
	 */
	F32 mScale;

	/** True will stop the time counting
	 */
	bool mIsPaused;

public:
	explicit Clock(U64 baseTimeNanoSeconds = 0) :
		mScale(1.0f),
		mIsPaused(true),
		mTotalNanoSeconds(baseTimeNanoSeconds) {}

	explicit Clock(U64 baseTimeNanoSeconds, float scale) :
		mScale(scale),
		mIsPaused(true),
		mTotalNanoSeconds(baseTimeNanoSeconds) {}

	explicit Clock(U64 baseTimeNanoSeconds, float scale, bool paused) :
		mScale(scale),
		mIsPaused(paused),
		mTotalNanoSeconds(baseTimeNanoSeconds) {}

	~Clock() {}

	/**
	 * One tick update
	 * @note will have no effect if the clock is paused
	 * @param dtNanoSecond amount of time to append to the clock's total elapsed time
	 */
	void update(U32 dtNanoSecond);

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

	U32 getLastFrameElapsedTime() const;

	float getLastFrameElapsedTimeAsSecond() const;

	U64 getTotalTime() const;
};
}

#endif //GANESHENGINE_GHCLOCK_H
