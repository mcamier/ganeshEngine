#ifndef GANESHENGINE_GHPLATFORM_H
#define GANESHENGINE_GHPLATFORM_H

#include "ghHeaders.h"
#include "ghSystem.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ganeshEngine {

/**
 * Read some system informations about the system like the screen framerate,
 * the screen resolution, the CPU speed and so on.
 */
class Platform : public System<Platform> {
    friend class System<Platform>;

private:
    GLFWwindow *mpWindow {nullptr};

protected:
    void vInitialize() override;
    void vDestroy() override;

public:
    GLFWwindow* getWindow() const;

    /**
     * Getter to screen's height read from system
     *
     * @return screen's width as U16
     */
    const U16 getScreenHeight();

    /**
     * Getter to screen's width read from system
     *
     * @return screen's height as U16
     */
    const U16 getScreenWidth();

    /**
     * Getter to screen's refresh rate read from system
     *
     * @return screen's refresh rate as U16
     */
    const U16 getScreenRefreshRate();

    /**
     * Getter to CPU core amount
     *
     * @return screen's refresh rate as U16
     */
    const U16 getCpuCoreAmount();
};

/**
 * Global getter of reference to the Platform
 * @return reference to the Platform
 */
extern Platform&(*gPlatform)();

}

#endif //GANESHENGINE_GHPLATFORM_H
