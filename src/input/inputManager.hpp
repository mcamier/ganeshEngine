#ifndef RENDERENGINEPLAYGROUND_INPUTMANAGER_HPP
#define RENDERENGINEPLAYGROUND_INPUTMANAGER_HPP

#include "../common/managers.hpp"
#include "../input/input.hpp"

namespace rep
{

typedef struct inputKeyboardState
{
    inputActionButton action;
    inputModifierFlag modifier;
} inputKeyboardState;

typedef struct inputMousePosition
{
    double x;
    double y;
} inputMousePosition ;
typedef inputMousePosition inputMouseScroll;


//
struct InputManagerInitializeArgs_t
{
};


//
class InputManager :
        public SingletonManager<InputManager, InputManagerInitializeArgs_t>
{

private:
    inputMousePosition lastPosition;
    inputMousePosition lastEventPosition;

    inputMouseScroll lastEventScroll;

    inputKeyboardState lastFrameKeyState[INPUT_KEY_COUNT];
    inputKeyboardState currentFrameKeyState[INPUT_KEY_COUNT];

protected:
    void vInit(InputManagerInitializeArgs_t initStructArg);

    void vDestroy();

public:
    void vUpdate();

    void registerMouseMouveInput(double xpos, double ypos);

    void registerMouseScrollInput(double offsetX, double offsetY);

    void registerKeyboardInput(inputKeyboardKey key, int scancode, inputActionButton action, inputModifierFlag mods);

    void registerMouseButtonInput(inputMouseButton button, inputActionButton action, inputModifierFlag mods);

    bool isMouseMoved(double *xpos, double *ypos);

    bool isMouseScrolled(double *offsetX, double *offsetY);

    bool isKeyPressedOnce(inputKeyboardKey key);

};

}

#endif //RENDERENGINEPLAYGROUND_INPUTMANAGER_HPP
