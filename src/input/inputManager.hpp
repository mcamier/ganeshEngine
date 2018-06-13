#ifndef RENDERENGINEPLAYGROUND_INPUTMANAGER_HPP
#define RENDERENGINEPLAYGROUND_INPUTMANAGER_HPP

#include "../common/managers.hpp"
#include "../input/input.hpp"

namespace rep
{

typedef struct inputMousePosition
{
    double x;
    double y;
} inputMousePosition ;


/**
 *
 */
struct InputManagerInitializeArgs_t
{
};


/**
 *
 */
class InputManager :
        public SingletonManager<InputManager, InputManagerInitializeArgs_t>
{

private:
    /**
     * Mouse
     */
    inputMousePosition lastPosition;
    inputMousePosition lastEventPosition;

protected:
    void vInit(InputManagerInitializeArgs_t initStructArg);

    void vDestroy();

public:
    void vUpdate();

    void registerMouseMouveInput(double xpos, double ypos);

    void registerMouseButtonInput(inputMouseButton button, inputActionButton action, inputModifierFlag mods);

    bool isMouseMoved(double *xpos, double *ypos);

    bool isKeyPressed(int key);

};

}


#endif //RENDERENGINEPLAYGROUND_INPUTMANAGER_HPP
