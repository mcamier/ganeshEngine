#ifndef RENDERENGINEPLAYGROUND_INPUT_GLFW_HPP
#define RENDERENGINEPLAYGROUND_INPUT_GLFW_HPP

#include <cstdint>

#include <GLFW/glfw3.h>

#include "input.hpp"

namespace rep
{

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


inputActionButton convertGlfwInputAction(int glfwInputAction)
{
    if (GLFW_PRESS == glfwInputAction) return INPUT_ACTION_PRESS;
    if (GLFW_RELEASE == glfwInputAction) return INPUT_ACTION_RELEASE;
    return INPUT_ACTION_NONE;
}


inputModifierFlag convertGlfwInputModifier(int glfwInputModifier)
{
    inputModifierFlag modifier = INPUT_MODIFIER_NONE;
    modifier &= ((glfwInputModifier & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT) ? INPUT_MODIFIER_SHIFT : modifier;
    modifier &= ((glfwInputModifier & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL) ? INPUT_MODIFIER_CONTROL : modifier;
    modifier &= ((glfwInputModifier & GLFW_MOD_ALT) == GLFW_MOD_ALT) ? INPUT_MODIFIER_ALT : modifier;
    modifier &= ((glfwInputModifier & GLFW_MOD_SUPER) == GLFW_MOD_SUPER) ? INPUT_MODIFIER_SUPER : modifier;
    return modifier;
}

}

#endif //RENDERENGINEPLAYGROUND_INPUT_GLFW_HPP
