#ifndef GANESHENGINE_GHIWINDOW_H
#define GANESHENGINE_GHIWINDOW_H

#include <cassert>
#include <string>
#include <util/ghClock.hpp>

namespace ganeshEngine {

class IWindow {
private:
    /**
     * Boolean flag used to enforce the uniqueness of the instance of this class
     * <p>
     * @note Replace usage of singleton pattern, because no need of global for this object, only single instance at a time
     */
    bool mbInstanceCreated = false;

public:
    /**
     * Constructor of the single-instance class IWindow
     * <p>
     * int parameter value is unrelevant, just here to force user to use base class constructor in order to
     * enforce setting of mbInstanceCreated
     *
     * @todo test weakness on multithread usage
     */
    explicit IWindow(int value) {
        assert(!mbInstanceCreated);
        mbInstanceCreated = true;
    }

    ~IWindow() {
        mbInstanceCreated = false;
    }

    /**
     * Overload this method in order to implement initialization of the concrete window and input wrapping API
     */
    virtual void vInitialize() = 0;

    /**
     * Overload this method in order to implement destruction of the concrete window and input wrapping API
     */
    virtual void vDestroy() = 0;

    /**
     * Overload this method in order to swap buffers through the underlying API
     */
    virtual void swapBuffer() = 0;

    /**
     * Overload this method in order to poll events through the underlying API
     */
    virtual void pollEvents() = 0;

    /**
     * Set a new name for the window, could be used to change the displayed name of the window
     * @param newName new name for the window
     */
    virtual void setName(const std::string& newName) = 0;

    /**
     * Get the current name of the window
     * @return Current name of the window
     */
    virtual std::string getName() = 0;

    /**
     * Get the current fullscreen state of the window
     * @return true if fullscreen, false otherwise
     */
    virtual bool isFullscreen() = 0;

    /**
     * Set the fullscreen state of the window
     * @param isFullscreen true to set fullscreen mode, or false for windowed mode
     */
    virtual void setFullscreen(bool isFullscreen) = 0;
};

}

#endif //GANESHENGINE_GHIWINDOW_H