#include "inputManager.hpp"
#include "../common/logger.hpp"

namespace rep
{

void InputManager::vInit(InputManagerInitializeArgs_t initStructArg)
{
}


void InputManager::vDestroy()
{

}


void InputManager::vUpdate()
{
    lastEventPosition = {-1 , -1};
}


void InputManager::registerMouseMouveInput(double xpos, double ypos)
{
    if(lastEventPosition.x != -1 && lastEventPosition.y != -1)
    {
        lastPosition = lastEventPosition;
    }
    lastEventPosition = {xpos , ypos};
}


void InputManager::registerMouseButtonInput(inputMouseButton button, inputActionButton action, inputModifierFlag mods)
{
}


bool InputManager::isMouseMoved(double *xpos, double *ypos)
{
    if(lastEventPosition.x != -1 && lastEventPosition.y != -1)
    {
        *xpos = lastEventPosition.x;
        *ypos = lastEventPosition.y;
        return true;
    }
    return false;
}

};
