#include "input/ghJoystick.hpp"

namespace ganeshEngine {


Joystick::~Joystick() {
    if (mInitialized) {
        std::free(mPreviousAxeStates);
        std::free(mPreviousButtonStates);
    }
}


void Joystick::initialize(int index) {
    /*if (glfwJoystickPresent(index)) {
        mIndex = index;
        mConnected = true;
        mInitialized = true;
        mAxeStates = glfwGetJoystickAxes(index, &mAxesCount);
        mButtonStates = glfwGetJoystickButtons(index, &mButtonsCount);

        mPreviousAxeStates = (float *) std::malloc(mAxesCount * sizeof(float));
        mPreviousButtonStates = (unsigned char *) std::malloc(mButtonsCount * sizeof(unsigned char));

        for(int i = 0 ; i < mAxesCount ; i++) {
            mPreviousButtonStates[i] = 0.0f;
        }
        for(int i = 0 ; i < mButtonsCount ; i++) {
            mPreviousButtonStates[i] = 0;
        }
    } else {
        mConnected = false;
        mInitialized = false;
        mIndex = 0;
        mAxesCount = 0;
        mButtonsCount = 0;
        mAxeStates = nullptr;
        mPreviousAxeStates = nullptr;
        mButtonStates = nullptr;
        mPreviousButtonStates = nullptr;
    }*/
}

void Joystick::release() {
    if (mConnected && mInitialized) {
        mConnected = false;
        mInitialized = false;
        mAxeStates = nullptr;
        mButtonStates = nullptr;
        mAxesCount = 0;
        mButtonsCount = 0;

        std::free(mPreviousAxeStates);
        std::free(mPreviousButtonStates);
    }
}

void Joystick::update() {
    /*if (mConnected && mInitialized) {
        // update joystick state
        mAxeStates = glfwGetJoystickAxes(mIndex, &mAxesCount);
        mButtonStates = glfwGetJoystickButtons(mIndex, &mButtonsCount);

        // Read buttons states to submit input to manager if needed
        RawInput rawInput;
        for (int i = 0; i < mButtonsCount; i++) {
            rawInput = RawInput();
            rawInput.idx = this->mIndex;
            rawInput.source = InputSource::DEVICE;
            rawInput.code = InputCode::UNSUPPORTED;

            if (mButtonStates[i] == GLFW_PRESS) {
                rawInput.type = InputType::BUTTON_PRESS;
            }

            if (mPreviousButtonStates[i] == GLFW_RELEASE && mButtonStates[i] == GLFW_PRESS) {
                rawInput.type = InputType::BUTTON_PRESS;
                rawInput.code = mapButtonIdxToInputCode(i);
            }
            else if (mPreviousButtonStates[i] == GLFW_PRESS && mButtonStates[i] == GLFW_PRESS) {
                rawInput.type = InputType::BUTTON_DOWN;
                rawInput.code = mapButtonIdxToInputCode(i);
            }
            else if (mPreviousButtonStates[i] == GLFW_PRESS && mButtonStates[i] == GLFW_RELEASE) {
                rawInput.type = InputType::BUTTON_RELEASE;
                rawInput.code = mapButtonIdxToInputCode(i);
            }

            if (rawInput.code != InputCode::UNSUPPORTED) {
                gInput().registerInput(rawInput);
            }
        }

        // Read axes states to submit input to manager if needed
        for (int i = 0; i < mAxesCount; i++) {
            rawInput = RawInput();
            rawInput.idx = this->mIndex;
            rawInput.source = InputSource::DEVICE;
            rawInput.type = InputType::AXIS;
            rawInput.code = InputCode::UNSUPPORTED;
            rawInput.code = mapAxesIdxToInputCode(i);


            if( rawInput.code == InputCode::XBOX_CONTROLLER_AXIS_RT ||
                rawInput.code == InputCode::XBOX_CONTROLLER_AXIS_LT ) {

                if(mAxeStates[i] > -1.0f && mAxeStates[i] <= 1.0f) {
                    gInput().registerInput(rawInput);
                }
            } else if ( (rawInput.code != InputCode::UNSUPPORTED) &&
                        (mAxeStates[i] < -0.1f || mAxeStates[i] > 0.1f) ) {
                gInput().registerInput(rawInput);
            }
        }

        std::memcpy(mPreviousAxeStates, mAxeStates, mAxesCount * sizeof(float));
        std::memcpy(mPreviousButtonStates, mButtonStates, mButtonsCount * sizeof(unsigned char));
    }*/
}

InputCode Joystick::mapButtonIdxToInputCode(int idx) {
    switch (idx) {
        case 0:
            return InputCode::XBOX_CONTROLLER_A;
        case 1:
            return InputCode::XBOX_CONTROLLER_B;
        case 2:
            return InputCode::XBOX_CONTROLLER_X;
        case 3:
            return InputCode::XBOX_CONTROLLER_Y;
        case 4:
            return InputCode::XBOX_CONTROLLER_LB;
        case 5:
            return InputCode::XBOX_CONTROLLER_RB;
        case 6:
            return InputCode::XBOX_CONTROLLER_SELECT;
        case 7:
            return InputCode::XBOX_CONTROLLER_START;
        case 8:
            return InputCode::XBOX_CONTROLLER_LS;
        case 9:
            return InputCode::XBOX_CONTROLLER_RS;
        case 10:
            return InputCode::XBOX_CONTROLLER_UP;
        case 11:
            return InputCode::XBOX_CONTROLLER_RIGHT;
        case 12:
            return InputCode::XBOX_CONTROLLER_DOWN;
        case 13:
            return InputCode::XBOX_CONTROLLER_LEFT;
        default:
            return InputCode::UNSUPPORTED;
    };
}

InputCode Joystick::mapAxesIdxToInputCode(int idx) {
    switch (idx) {
        case 0:
            return InputCode::XBOX_CONTROLLER_AXIS_LEFT_X;
        case 1:
            return InputCode::XBOX_CONTROLLER_AXIS_LEFT_Y;
        case 2:
            return InputCode::XBOX_CONTROLLER_AXIS_RIGHT_X;
        case 3:
            return InputCode::XBOX_CONTROLLER_AXIS_RIGHT_Y;
        case 4:
            return InputCode::XBOX_CONTROLLER_AXIS_RT;
        case 5:
            return InputCode::XBOX_CONTROLLER_AXIS_LT;
        default:
            return InputCode::UNSUPPORTED;
    };
}

}