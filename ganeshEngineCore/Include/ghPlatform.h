#ifndef GANESHENGINE_GHPLATFORM_H
#define GANESHENGINE_GHPLATFORM_H

#include "ghHeaders.h"

namespace ganeshEngine {

/** This read some system informations about the system like the screen framerate,
 *  the screen resolution, the CPU speed and so one.
 */
class Platform {
private:

public:
    Platform() {}
    Platform(const Platform&) = delete;
    Platform& operator=(const Platform&) = delete;
    ~Platform() {}

    /** Getter to screen's height read from system
     *
     * \return screen's width as U16
     */
    static const U16 getScreenHeight();

    /** Getter to screen's width read from system
     *
     * \return screen's height as U16
     */
    static const U16 getScreenWidth();

    /** Getter to screen's refresh rate read from system
     *
     * \return screen's refresh rate as U16
     */
    static const U16 getScreenRefreshRate();

    /** Getter to CPU core amount
     *
     * \return screen's refresh rate as U16
     */
    static const U16 getCpuCoreAmount();
};

}

#endif //GANESHENGINE_GHPLATFORM_H
