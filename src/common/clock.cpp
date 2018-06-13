#include "clock.hpp"


namespace rep
{

void Clock::update(uint32_t dtNanoSecond)
{
    if (!mIsPaused)
    {
        mLastTimeAdded = mScale * dtNanoSecond;
        mTotalNanoSeconds += mLastTimeAdded;
    }
    else
    {
        mLastTimeAdded = 0;
    }
}

bool Clock::isPaused()
{
    return mIsPaused;
}

void Clock::setPause(bool value)
{
    mIsPaused = value;
}

uint32_t Clock::getLastFrameElapsedTime() const
{
    return mLastTimeAdded;
}

uint64_t Clock::getTotalTime() const
{
    return mTotalNanoSeconds;
}

float Clock::getLastFrameElapsedTimeAsSecond() const
{
    return (float) (mLastTimeAdded) / 1000000000.0f;
}

}
