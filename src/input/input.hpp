#ifndef RENDERENGINEPLAYGROUND_INPUT_HPP
#define RENDERENGINEPLAYGROUND_INPUT_HPP

#include <cstdint>

#include <GLFW/glfw3.h>

namespace rep
{

//
typedef enum inputMouseButton
{
    INPUT_MOUSE_BUTTON_1 = 0,
    INPUT_MOUSE_BUTTON_2 = 1,
    INPUT_MOUSE_BUTTON_3 = 2,
    INPUT_MOUSE_BUTTON_4 = 3,
    INPUT_MOUSE_BUTTON_5 = 4,
    INPUT_MOUSE_BUTTON_6 = 5,
    INPUT_MOUSE_BUTTON_7 = 6,
    INPUT_MOUSE_BUTTON_8 = 7,
    INPUT_MOUSE_BUTTON_LEFT = INPUT_MOUSE_BUTTON_1,
    INPUT_MOUSE_BUTTON_RIGHT = INPUT_MOUSE_BUTTON_2,
    INPUT_MOUSE_BUTTON_MIDDLE = INPUT_MOUSE_BUTTON_3,
    INPUT_MOUSE_BUTTON_LAST = INPUT_MOUSE_BUTTON_8,

} inputMouseButton;


//
typedef enum inputActionButton
{
    INPUT_ACTION_NONE = -1,
    INPUT_ACTION_PRESS = 0,
    INPUT_ACTION_RELEASE = 1,

} inputActionButton;


//
typedef enum inputModifierBitsFlag
{
    INPUT_MODIFIER_NONE = 0,
    INPUT_MODIFIER_SHIFT = 1 << 0,
    INPUT_MODIFIER_CONTROL = 1 << 1,
    INPUT_MODIFIER_ALT = 1 << 2,
    INPUT_MODIFIER_SUPER = 1 << 3

} inputModifierBitsFlag;
typedef uint8_t inputModifierFlag;

} // namespace rep

#endif //RENDERENGINEPLAYGROUND_INPUT_GLFW_HPP
