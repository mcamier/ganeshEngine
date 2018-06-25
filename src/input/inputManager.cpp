#include "inputManager.hpp"
#include "../common/logger.hpp"

namespace ge {
namespace input {

void InputManager::vInit(InputManagerInitializeArgs_t initStructArg) {
    for (int i = 0; i < INPUT_KEY_COUNT; i++) {
        keyState[i] = {INPUT_ACTION_NONE, INPUT_MODIFIER_NONE};
    }
}


void InputManager::vDestroy() {

}


void InputManager::vUpdate() {
    lastEventPosition = {-1, -1};
    lastEventScroll = {0, 0};
}


void InputManager::registerMouseMouveInput(double xpos, double ypos) {
    if (lastEventPosition.x != -1 && lastEventPosition.y != -1) {
        lastPosition = lastEventPosition;
    }
    lastEventPosition = {xpos, ypos};
}


void InputManager::registerMouseButtonInput(inputMouseButton button, inputActionButton action, inputModifierFlag mods) {
}


void InputManager::registerMouseScrollInput(double offsetX, double offsetY) {
    lastEventScroll = {offsetX, offsetY};
}


void InputManager::registerKeyboardInput(inputKeyboardKey key, inputActionButton action, inputModifierFlag mods) {
    inputKeyboardState state = {};
    state.modifier = mods;
    if (keyState[key].action != INPUT_ACTION_PRESS &&
        keyState[key].action != INPUT_ACTION_NONE) {
        state.action = INPUT_ACTION_REPEAT;
    } else {
        state.action = action;
    }

    //REP_DEBUG("keyboard input " << action << ", modifier " << mods , LogChannelBitsFlag::RENDER)

    keyState[key] = {action, mods};
}


bool InputManager::isMouseMoved(double *xpos, double *ypos, double *xDeltaLastPosition, double *yDeltaLastPosition) {
    if (lastEventPosition.x != -1 && lastEventPosition.y != -1) {
        if (xDeltaLastPosition != nullptr) {
            *xDeltaLastPosition = lastPosition.x - lastEventPosition.x;
        }
        if (yDeltaLastPosition != nullptr) {
            *yDeltaLastPosition = lastPosition.y - lastEventPosition.y;
        }

        if (xpos != nullptr) {
            *xpos = lastEventPosition.x;
        }
        if (ypos != nullptr) {
            *ypos = lastEventPosition.y;
        }
        return true;
    }
    return false;
}


bool InputManager::isMouseScrolled(double *offsetX, double *offsetY) {
    if (lastEventScroll.x != 0 || lastEventScroll.y != 0) {
        *offsetX = lastEventScroll.x;
        *offsetY = lastEventScroll.y;
        return true;
    }
    return false;
}


bool InputManager::isKeyPressedOnce(inputKeyboardKey key) {
    return false;
}


} // namespace input
} // namespace ge