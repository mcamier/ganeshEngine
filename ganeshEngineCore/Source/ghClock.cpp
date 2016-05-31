#include "ghClock.h"

namespace ganeshEngine {

void Clock::tick(U32 dtNanoSecond) {
    if(!mIsPaused) {
        mTotalNanoSeconds += mScale * dtNanoSecond;
    }
}


void Clock::singleStep(bool force) {
    if(!mIsPaused || force) {
        tick((1.0f/30.0f) * 1000000000);
    }
}

    bool Clock::isPaused() {
    return mIsPaused;
}

void Clock::setPause(bool value) {
    mIsPaused = value;
}

}
