#ifndef GANESHENGINE_GHIWINDOW_H
#define GANESHENGINE_GHIWINDOW_H

#include <cassert>

class IWindow {
private:
    bool mbInstanceCreated = false;

public:
    /**
     * Constructor of the single-instance IWindow
     *
     * @note int parameter value is unrelevant, just here to force user to use base class constructor in order to
     * enforce setting of mbInstanceCreated
     * @note test weakness on multithread usage
     * @return
     */
    explicit IWindow(int value) {
        assert(!mbInstanceCreated);
        mbInstanceCreated = true;
    }

    ~IWindow() {
        mbInstanceCreated = false;
    }

    virtual void vInitialize() = 0;

    virtual void vDestroy() = 0;
};

#endif //GANESHENGINE_GHIWINDOW_H