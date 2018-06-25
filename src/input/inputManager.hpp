#ifndef GE_INPUTMANAGER_HPP
#define GE_INPUTMANAGER_HPP

#include "../common/managers.hpp"
#include "../input/input.hpp"

namespace ge
{
namespace input
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
    inputMousePosition lastPosition = {0, 0};
    inputMousePosition lastEventPosition = {0, 0};

    inputMouseScroll lastEventScroll;

    inputKeyboardState keyState[INPUT_KEY_COUNT];

protected:
    void vInit(InputManagerInitializeArgs_t initStructArg);

    void vDestroy();

public:
    void vUpdate();

    void registerMouseMouveInput(double xpos, double ypos);

    void registerMouseScrollInput(double offsetX, double offsetY);

    void registerKeyboardInput(inputKeyboardKey key, inputActionButton action, inputModifierFlag mods);

    void registerMouseButtonInput(inputMouseButton button, inputActionButton action, inputModifierFlag mods);

    bool isMouseMoved(double *xpos, double *ypos, double *xDeltaLastPosition, double *yDeltaLastPosition);

    bool isMouseScrolled(double *offsetX, double *offsetY);

    bool isKeyPressedOnce(inputKeyboardKey key);

};

}
}

#endif //GE_INPUTMANAGER_HPP
