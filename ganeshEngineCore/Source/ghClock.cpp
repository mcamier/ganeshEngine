#include "ghClock.h"

namespace ganeshEngine {

void Clock::update(U32 dtNanoSecond) {
	if (!mIsPaused) {
		mLastTimeAdded = mScale * dtNanoSecond;
		mTotalNanoSeconds += mLastTimeAdded;
	} else {
		mLastTimeAdded = 0;
	}
}

bool Clock::isPaused() {
	return mIsPaused;
}

void Clock::setPause(bool value) {
	mIsPaused = value;
}

U32 Clock::getLastFrameElapsedTime() const {
	return mLastTimeAdded;
}

U64 Clock::getTotalTime() const {
	return mTotalNanoSeconds;
}

float Clock::getLastFrameElapsedTimeAsSecond() const {
	return (float)(mLastTimeAdded)/1000000000.0f;
}

}
