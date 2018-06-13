#include "inputManager.hpp"

namespace rep
{

void InputManager::vInit(InputManagerInitializeArgs_t initStructArg)
{
    for (int i = 0; i < INPUT_KEY_COUNT; i++)
    {
        currentFrameKeyState[i] = {INPUT_ACTION_NONE, INPUT_MODIFIER_NONE};
        lastFrameKeyState[i] = currentFrameKeyState[i];
    }
}


void InputManager::vDestroy()
{

}


void InputManager::vUpdate()
{
    lastEventPosition = {-1, -1};
    lastEventScroll = {0, 0};
    for (int i = 0; i < INPUT_KEY_COUNT; i++)
    {
        lastFrameKeyState[i] = currentFrameKeyState[i];
        currentFrameKeyState[i] = {INPUT_ACTION_NONE, INPUT_MODIFIER_NONE};
    }
}


void InputManager::registerMouseMouveInput(double xpos, double ypos)
{
    if (lastEventPosition.x != -1 && lastEventPosition.y != -1)
    {
        lastPosition = lastEventPosition;
    }
    lastEventPosition = {xpos, ypos};
}


void InputManager::registerMouseButtonInput(inputMouseButton button, inputActionButton action, inputModifierFlag mods)
{
}


void InputManager::registerMouseScrollInput(double offsetX, double offsetY)
{
    lastEventScroll = {offsetX, offsetY};
}


void InputManager::registerKeyboardInput(inputKeyboardKey key, int scancode, inputActionButton action,
                                         inputModifierFlag mods)
{
    currentFrameKeyState[key] = {action, mods};
}


bool InputManager::isMouseMoved(double *xpos, double *ypos)
{
    if (lastEventPosition.x != -1 && lastEventPosition.y != -1)
    {
        *xpos = lastEventPosition.x;
        *ypos = lastEventPosition.y;
        return true;
    }
    return false;
}


bool InputManager::isMouseScrolled(double *offsetX, double *offsetY)
{
    if (lastEventScroll.x != 0 || lastEventScroll.y != 0)
    {
        *offsetX = lastEventScroll.x;
        *offsetY = lastEventScroll.y;
        return true;
    }
    return false;
}


bool InputManager::isKeyPressedOnce(inputKeyboardKey key)
{
    return currentFrameKeyState[key].action == INPUT_ACTION_PRESS;
}

};
