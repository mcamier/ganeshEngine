#ifndef GE_CLOCK_H
#define GE_CLOCK_H

#include <cstdint>

namespace ge
{

class Clock
{
private:

    // Total nanoseconds elapsed
    uint64_t mTotalNanoSeconds;

    uint32_t mLastTimeAdded;

    // Define how time elapsed
    //  Value of 1.0f will let time elapsed normally
    //  Value of 2.0f will make things happens two times quicker
    //  Value of 0.5f will make things happens two times lower
    float mScale;

    // True will stop the time counting
    bool mIsPaused;

public:
    explicit Clock(uint64_t baseTimeNanoSeconds = 0) :
            mTotalNanoSeconds(baseTimeNanoSeconds),
            mLastTimeAdded(0),
            mScale(1.0f),
            mIsPaused(true)
    {}

    explicit Clock(uint64_t baseTimeNanoSeconds, float scale) :
            mTotalNanoSeconds(baseTimeNanoSeconds),
            mLastTimeAdded(0),
            mScale(scale),
            mIsPaused(true)
    {}

    explicit Clock(uint64_t baseTimeNanoSeconds, float scale, bool paused) :
            mTotalNanoSeconds(baseTimeNanoSeconds),
            mLastTimeAdded(0),
            mScale(scale),
            mIsPaused(paused)
    {}

    ~Clock()
    {}

    // One tick update
    // @note will have no effect if the clock is paused
    // @param dtNanoSecond amount of time to append to the clock's total elapsed time
    void update(uint32_t dtNanoSecond);

    // Getter of pause status
    // Return True if the clock is paused, false otherwise
    bool isPaused();

    // Setter of pause status
    // @param value True to pause the clock, false otherwise
    void setPause(bool value);

    uint32_t getLastFrameElapsedTime() const;

    float getLastFrameElapsedTimeAsSecond() const;

    uint64_t getTotalTime() const;
};

} // namespace ge

#endif //GE_CLOCK_H
