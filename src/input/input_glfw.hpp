#ifndef RENDERENGINEPLAYGROUND_INPUT_GLFW_HPP
#define RENDERENGINEPLAYGROUND_INPUT_GLFW_HPP

#include <cstdint>

#include <GLFW/glfw3.h>

#include "input.hpp"

namespace rep
{

//
inputMouseButton convertGlfwInputMouseButton(int glfwMouseButton)
{
    if (GLFW_MOUSE_BUTTON_1 == glfwMouseButton) return INPUT_MOUSE_BUTTON_1;
    if (GLFW_MOUSE_BUTTON_2 == glfwMouseButton) return INPUT_MOUSE_BUTTON_2;
    if (GLFW_MOUSE_BUTTON_3 == glfwMouseButton) return INPUT_MOUSE_BUTTON_3;
    if (GLFW_MOUSE_BUTTON_4 == glfwMouseButton) return INPUT_MOUSE_BUTTON_4;
    if (GLFW_MOUSE_BUTTON_5 == glfwMouseButton) return INPUT_MOUSE_BUTTON_5;
    if (GLFW_MOUSE_BUTTON_6 == glfwMouseButton) return INPUT_MOUSE_BUTTON_6;
    if (GLFW_MOUSE_BUTTON_7 == glfwMouseButton) return INPUT_MOUSE_BUTTON_7;
    if (GLFW_MOUSE_BUTTON_8 == glfwMouseButton) return INPUT_MOUSE_BUTTON_8;
    if (GLFW_MOUSE_BUTTON_LEFT == glfwMouseButton) return INPUT_MOUSE_BUTTON_LEFT;
    if (GLFW_MOUSE_BUTTON_RIGHT == glfwMouseButton) return INPUT_MOUSE_BUTTON_RIGHT;
    if (GLFW_MOUSE_BUTTON_MIDDLE == glfwMouseButton) return INPUT_MOUSE_BUTTON_MIDDLE;
    if (GLFW_MOUSE_BUTTON_LAST == glfwMouseButton) return INPUT_MOUSE_BUTTON_LAST;
}


inputKeyboardKey convertGlfwInputKeyboardKey(int glfwKeyboardKey)
{
    if (GLFW_KEY_UNKNOWN == glfwKeyboardKey) return INPUT_KEY_UNKNOWN;
    if (GLFW_KEY_SPACE == glfwKeyboardKey) return INPUT_KEY_SPACE;
    if (GLFW_KEY_APOSTROPHE == glfwKeyboardKey) return INPUT_KEY_APOSTROPHE;
    if (GLFW_KEY_COMMA == glfwKeyboardKey) return INPUT_KEY_COMMA;
    if (GLFW_KEY_MINUS == glfwKeyboardKey) return INPUT_KEY_MINUS;
    if (GLFW_KEY_PERIOD == glfwKeyboardKey) return INPUT_KEY_PERIOD;
    if (GLFW_KEY_SLASH == glfwKeyboardKey) return INPUT_KEY_SLASH;
    if (GLFW_KEY_0 == glfwKeyboardKey) return INPUT_KEY_0;
    if (GLFW_KEY_1 == glfwKeyboardKey) return INPUT_KEY_1;
    if (GLFW_KEY_2 == glfwKeyboardKey) return INPUT_KEY_2;
    if (GLFW_KEY_3 == glfwKeyboardKey) return INPUT_KEY_3;
    if (GLFW_KEY_4 == glfwKeyboardKey) return INPUT_KEY_4;
    if (GLFW_KEY_5 == glfwKeyboardKey) return INPUT_KEY_5;
    if (GLFW_KEY_6 == glfwKeyboardKey) return INPUT_KEY_6;
    if (GLFW_KEY_7 == glfwKeyboardKey) return INPUT_KEY_7;
    if (GLFW_KEY_8 == glfwKeyboardKey) return INPUT_KEY_8;
    if (GLFW_KEY_9 == glfwKeyboardKey) return INPUT_KEY_9;
    if (GLFW_KEY_SEMICOLON == glfwKeyboardKey) return INPUT_KEY_SEMICOLON;
    if (GLFW_KEY_EQUAL == glfwKeyboardKey) return INPUT_KEY_EQUAL;
    if (GLFW_KEY_A == glfwKeyboardKey) return INPUT_KEY_A;
    if (GLFW_KEY_B == glfwKeyboardKey) return INPUT_KEY_B;
    if (GLFW_KEY_C == glfwKeyboardKey) return INPUT_KEY_C;
    if (GLFW_KEY_D == glfwKeyboardKey) return INPUT_KEY_D;
    if (GLFW_KEY_E == glfwKeyboardKey) return INPUT_KEY_E;
    if (GLFW_KEY_F == glfwKeyboardKey) return INPUT_KEY_F;
    if (GLFW_KEY_G == glfwKeyboardKey) return INPUT_KEY_G;
    if (GLFW_KEY_H == glfwKeyboardKey) return INPUT_KEY_H;
    if (GLFW_KEY_I == glfwKeyboardKey) return INPUT_KEY_I;
    if (GLFW_KEY_J == glfwKeyboardKey) return INPUT_KEY_J;
    if (GLFW_KEY_K == glfwKeyboardKey) return INPUT_KEY_K;
    if (GLFW_KEY_L == glfwKeyboardKey) return INPUT_KEY_L;
    if (GLFW_KEY_M == glfwKeyboardKey) return INPUT_KEY_M;
    if (GLFW_KEY_N == glfwKeyboardKey) return INPUT_KEY_N;
    if (GLFW_KEY_O == glfwKeyboardKey) return INPUT_KEY_O;
    if (GLFW_KEY_P == glfwKeyboardKey) return INPUT_KEY_P;
    if (GLFW_KEY_Q == glfwKeyboardKey) return INPUT_KEY_Q;
    if (GLFW_KEY_R == glfwKeyboardKey) return INPUT_KEY_R;
    if (GLFW_KEY_S == glfwKeyboardKey) return INPUT_KEY_S;
    if (GLFW_KEY_T == glfwKeyboardKey) return INPUT_KEY_T;
    if (GLFW_KEY_U == glfwKeyboardKey) return INPUT_KEY_U;
    if (GLFW_KEY_V == glfwKeyboardKey) return INPUT_KEY_V;
    if (GLFW_KEY_W == glfwKeyboardKey) return INPUT_KEY_W;
    if (GLFW_KEY_X == glfwKeyboardKey) return INPUT_KEY_X;
    if (GLFW_KEY_Y == glfwKeyboardKey) return INPUT_KEY_Y;
    if (GLFW_KEY_Z == glfwKeyboardKey) return INPUT_KEY_Z;
    if (GLFW_KEY_LEFT_BRACKET == glfwKeyboardKey) return INPUT_KEY_LEFT_BRACKET;
    if (GLFW_KEY_BACKSLASH == glfwKeyboardKey) return INPUT_KEY_BACKSLASH;
    if (GLFW_KEY_RIGHT_BRACKET == glfwKeyboardKey) return INPUT_KEY_RIGHT_BRACKET;
    if (GLFW_KEY_GRAVE_ACCENT == glfwKeyboardKey) return INPUT_KEY_GRAVE_ACCENT;
    if (GLFW_KEY_WORLD_1 == glfwKeyboardKey) return INPUT_KEY_WORLD_1;
    if (GLFW_KEY_WORLD_2 == glfwKeyboardKey) return INPUT_KEY_WORLD_2;
    if (GLFW_KEY_ESCAPE == glfwKeyboardKey) return INPUT_KEY_ESCAPE;
    if (GLFW_KEY_ENTER == glfwKeyboardKey) return INPUT_KEY_ENTER;
    if (GLFW_KEY_TAB == glfwKeyboardKey) return INPUT_KEY_TAB;
    if (GLFW_KEY_BACKSPACE == glfwKeyboardKey) return INPUT_KEY_BACKSPACE;
    if (GLFW_KEY_INSERT == glfwKeyboardKey) return INPUT_KEY_INSERT;
    if (GLFW_KEY_DELETE == glfwKeyboardKey) return INPUT_KEY_DELETE;
    if (GLFW_KEY_RIGHT == glfwKeyboardKey) return INPUT_KEY_RIGHT;
    if (GLFW_KEY_LEFT == glfwKeyboardKey) return INPUT_KEY_LEFT;
    if (GLFW_KEY_DOWN == glfwKeyboardKey) return INPUT_KEY_DOWN;
    if (GLFW_KEY_UP == glfwKeyboardKey) return INPUT_KEY_UP;
    if (GLFW_KEY_PAGE_UP == glfwKeyboardKey) return INPUT_KEY_PAGE_UP;
    if (GLFW_KEY_PAGE_DOWN == glfwKeyboardKey) return INPUT_KEY_PAGE_DOWN;
    if (GLFW_KEY_HOME == glfwKeyboardKey) return INPUT_KEY_HOME;
    if (GLFW_KEY_END == glfwKeyboardKey) return INPUT_KEY_END;
    if (GLFW_KEY_CAPS_LOCK == glfwKeyboardKey) return INPUT_KEY_CAPS_LOCK;
    if (GLFW_KEY_SCROLL_LOCK == glfwKeyboardKey) return INPUT_KEY_SCROLL_LOCK;
    if (GLFW_KEY_NUM_LOCK == glfwKeyboardKey) return INPUT_KEY_NUM_LOCK;
    if (GLFW_KEY_PRINT_SCREEN == glfwKeyboardKey) return INPUT_KEY_PRINT_SCREEN;
    if (GLFW_KEY_PAUSE == glfwKeyboardKey) return INPUT_KEY_PAUSE;
    if (GLFW_KEY_F1 == glfwKeyboardKey) return INPUT_KEY_F1;
    if (GLFW_KEY_F2 == glfwKeyboardKey) return INPUT_KEY_F2;
    if (GLFW_KEY_F3 == glfwKeyboardKey) return INPUT_KEY_F3;
    if (GLFW_KEY_F4 == glfwKeyboardKey) return INPUT_KEY_F4;
    if (GLFW_KEY_F5 == glfwKeyboardKey) return INPUT_KEY_F5;
    if (GLFW_KEY_F6 == glfwKeyboardKey) return INPUT_KEY_F6;
    if (GLFW_KEY_F7 == glfwKeyboardKey) return INPUT_KEY_F7;
    if (GLFW_KEY_F8 == glfwKeyboardKey) return INPUT_KEY_F8;
    if (GLFW_KEY_F9 == glfwKeyboardKey) return INPUT_KEY_F9;
    if (GLFW_KEY_F10 == glfwKeyboardKey) return INPUT_KEY_F10;
    if (GLFW_KEY_F11 == glfwKeyboardKey) return INPUT_KEY_F11;
    if (GLFW_KEY_F12 == glfwKeyboardKey) return INPUT_KEY_F12;
    if (GLFW_KEY_F13 == glfwKeyboardKey) return INPUT_KEY_F13;
    if (GLFW_KEY_F14 == glfwKeyboardKey) return INPUT_KEY_F14;
    if (GLFW_KEY_F15 == glfwKeyboardKey) return INPUT_KEY_F15;
    if (GLFW_KEY_F16 == glfwKeyboardKey) return INPUT_KEY_F16;
    if (GLFW_KEY_F17 == glfwKeyboardKey) return INPUT_KEY_F17;
    if (GLFW_KEY_F18 == glfwKeyboardKey) return INPUT_KEY_F18;
    if (GLFW_KEY_F19 == glfwKeyboardKey) return INPUT_KEY_F19;
    if (GLFW_KEY_F20 == glfwKeyboardKey) return INPUT_KEY_F20;
    if (GLFW_KEY_F21 == glfwKeyboardKey) return INPUT_KEY_F21;
    if (GLFW_KEY_F22 == glfwKeyboardKey) return INPUT_KEY_F22;
    if (GLFW_KEY_F23 == glfwKeyboardKey) return INPUT_KEY_F23;
    if (GLFW_KEY_F24 == glfwKeyboardKey) return INPUT_KEY_F24;
    if (GLFW_KEY_F25 == glfwKeyboardKey) return INPUT_KEY_F25;
    if (GLFW_KEY_KP_0 == glfwKeyboardKey) return INPUT_KEY_KP_0;
    if (GLFW_KEY_KP_1 == glfwKeyboardKey) return INPUT_KEY_KP_1;
    if (GLFW_KEY_KP_2 == glfwKeyboardKey) return INPUT_KEY_KP_2;
    if (GLFW_KEY_KP_3 == glfwKeyboardKey) return INPUT_KEY_KP_3;
    if (GLFW_KEY_KP_4 == glfwKeyboardKey) return INPUT_KEY_KP_4;
    if (GLFW_KEY_KP_5 == glfwKeyboardKey) return INPUT_KEY_KP_5;
    if (GLFW_KEY_KP_6 == glfwKeyboardKey) return INPUT_KEY_KP_6;
    if (GLFW_KEY_KP_7 == glfwKeyboardKey) return INPUT_KEY_KP_7;
    if (GLFW_KEY_KP_8 == glfwKeyboardKey) return INPUT_KEY_KP_8;
    if (GLFW_KEY_KP_9 == glfwKeyboardKey) return INPUT_KEY_KP_9;
    if (GLFW_KEY_KP_DECIMAL == glfwKeyboardKey) return INPUT_KEY_KP_DECIMAL;
    if (GLFW_KEY_KP_DIVIDE == glfwKeyboardKey) return INPUT_KEY_KP_DIVIDE;
    if (GLFW_KEY_KP_MULTIPLY == glfwKeyboardKey) return INPUT_KEY_KP_MULTIPLY;
    if (GLFW_KEY_KP_SUBTRACT == glfwKeyboardKey) return INPUT_KEY_KP_SUBTRACT;
    if (GLFW_KEY_KP_ADD == glfwKeyboardKey) return INPUT_KEY_KP_ADD;
    if (GLFW_KEY_KP_ENTER == glfwKeyboardKey) return INPUT_KEY_KP_ENTER;
    if (GLFW_KEY_KP_EQUAL == glfwKeyboardKey) return INPUT_KEY_KP_EQUAL;
    if (GLFW_KEY_LEFT_SHIFT == glfwKeyboardKey) return INPUT_KEY_LEFT_SHIFT;
    if (GLFW_KEY_LEFT_CONTROL == glfwKeyboardKey) return INPUT_KEY_LEFT_CONTROL;
    if (GLFW_KEY_LEFT_ALT == glfwKeyboardKey) return INPUT_KEY_LEFT_ALT;
    if (GLFW_KEY_LEFT_SUPER == glfwKeyboardKey) return INPUT_KEY_LEFT_SUPER;
    if (GLFW_KEY_RIGHT_SHIFT == glfwKeyboardKey) return INPUT_KEY_RIGHT_SHIFT;
    if (GLFW_KEY_RIGHT_CONTROL == glfwKeyboardKey) return INPUT_KEY_RIGHT_CONTROL;
    if (GLFW_KEY_RIGHT_ALT == glfwKeyboardKey) return INPUT_KEY_RIGHT_ALT;
    if (GLFW_KEY_RIGHT_SUPER == glfwKeyboardKey) return INPUT_KEY_RIGHT_SUPER;
    if (GLFW_KEY_MENU == glfwKeyboardKey) return INPUT_KEY_MENU;
    if (GLFW_KEY_LAST == glfwKeyboardKey) return INPUT_KEY_LAST;
}


//
inputActionButton convertGlfwInputAction(int glfwInputAction)
{
    if (GLFW_PRESS == glfwInputAction) return INPUT_ACTION_PRESS;
    if (GLFW_RELEASE == glfwInputAction) return INPUT_ACTION_RELEASE;
    if (GLFW_REPEAT  == glfwInputAction) return INPUT_ACTION_REPEAT;
    return INPUT_ACTION_NONE;
}


//
inputModifierFlag convertGlfwInputModifier(int glfwInputModifier)
{
    inputModifierFlag modifier = INPUT_MODIFIER_NONE;
    modifier &= ((glfwInputModifier & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT) ? INPUT_MODIFIER_SHIFT : modifier;
    modifier &= ((glfwInputModifier & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL) ? INPUT_MODIFIER_CONTROL : modifier;
    modifier &= ((glfwInputModifier & GLFW_MOD_ALT) == GLFW_MOD_ALT) ? INPUT_MODIFIER_ALT : modifier;
    modifier &= ((glfwInputModifier & GLFW_MOD_SUPER) == GLFW_MOD_SUPER) ? INPUT_MODIFIER_SUPER : modifier;
    return modifier;
}

} // namespace rep

#endif //RENDERENGINEPLAYGROUND_INPUT_GLFW_HPP
