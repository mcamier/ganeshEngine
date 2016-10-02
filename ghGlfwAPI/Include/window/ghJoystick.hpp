#ifndef GANESHENGINE_GHJOYSTICK_H
#define GANESHENGINE_GHJOYSTICK_H

#include <input/ghInputUtils.hpp>

namespace ganeshEngine {

class Joystick {
protected:
    int mIndex;
    int mAxesCount;
    int mButtonsCount;
    bool mConnected;
    bool mInitialized;

    const float* mAxeStates;
    float* mPreviousAxeStates;

    const unsigned char* mButtonStates;
    unsigned char* mPreviousButtonStates;

public:
    Joystick() :
            mIndex(-1),
            mAxesCount(0),
            mButtonsCount(0),
            mConnected(false),
            mInitialized(false),
            mAxeStates(nullptr),
            mPreviousAxeStates(nullptr),
            mButtonStates(nullptr),
            mPreviousButtonStates(nullptr) {}

    virtual ~Joystick();

    /**
     * Must be initialize when the system input handler detect the given controller get plugged. Set the initial state of
     * controller.
     *
     * @param index index of the joystick
     */
    void initialize(int index);

    /**
     * Must be released when the system input handler detect the given controller get unplugged.
     */
    void release();

    /**
     * Copy the actual controller's state in order to be the "previous" state during the next frame.
     * Do nothing if could upon a controller not plugged or not initialized.
     */
    void update();

protected:
    InputCode mapButtonIdxToInputCode(int idx);

    InputCode mapAxesIdxToInputCode(int idx);
};

}

#endif //GANESHENGINE_GHJOYSTICK_H
