#ifndef GANESHENGINE_GHCLOCK_H
#define GANESHENGINE_GHCLOCK_H

#include "ghCore.h"

namespace ganeshEngine {

class Clock {
private:
    U64 mTotalNanoSeconds;
    F32 mScale;
    bool mIsPaused;

public:
    Clock(U64 baseTimeNanoSeconds = 0) : mScale(1.0f), mIsPaused(true), mTotalNanoSeconds(baseTimeNanoSeconds) {}
    Clock(const Clock&) = delete;
    Clock& operator=(const Clock&) = delete;
    ~Clock() {}

    /** One tick update clock
     */
    void tick(U32 dtNanoSecond);

    /** One tick update clock
     */
    void singleStep(bool force);

    /** Getter of pause status
     *
     * \param[in] Boolean to determine the status of the clock
     */
    bool isPaused();

    /** Setter of pause status
     *
     * \return True if the clock is paused, False otherwise
     */
    void setPause(bool value);
};

}

#endif //GANESHENGINE_GHCLOCK_H
