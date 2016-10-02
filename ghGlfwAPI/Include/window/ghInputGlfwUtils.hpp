#ifndef GANESHENGINE_GHINPUTGLFWUTILS_H
#define GANESHENGINE_GHINPUTGLFWUTILS_H

namespace ganeshEngine {

InputCode sysInputKeyboardCode2GHCode(int sysInputCode) {
    if (sysInputCode == GLFW_KEY_SPACE) { return InputCode::KEYBOARD_SPACE; }
    if (sysInputCode == GLFW_KEY_APOSTROPHE) { return InputCode::KEYBOARD_APOSTROPHE; }
    if (sysInputCode == GLFW_KEY_COMMA) { return InputCode::KEYBOARD_COMMA; }
    if (sysInputCode == GLFW_KEY_MINUS) { return InputCode::KEYBOARD_MINUS; }
    if (sysInputCode == GLFW_KEY_PERIOD) { return InputCode::KEYBOARD_PERIOD; }
    if (sysInputCode == GLFW_KEY_SLASH) { return InputCode::KEYBOARD_SLASH; }
    if (sysInputCode == GLFW_KEY_0) { return InputCode::KEYBOARD_0; }
    if (sysInputCode == GLFW_KEY_1) { return InputCode::KEYBOARD_1; }
    if (sysInputCode == GLFW_KEY_2) { return InputCode::KEYBOARD_2; }
    if (sysInputCode == GLFW_KEY_3) { return InputCode::KEYBOARD_3; }
    if (sysInputCode == GLFW_KEY_4) { return InputCode::KEYBOARD_4; }
    if (sysInputCode == GLFW_KEY_5) { return InputCode::KEYBOARD_5; }
    if (sysInputCode == GLFW_KEY_6) { return InputCode::KEYBOARD_6; }
    if (sysInputCode == GLFW_KEY_7) { return InputCode::KEYBOARD_7; }
    if (sysInputCode == GLFW_KEY_8) { return InputCode::KEYBOARD_8; }
    if (sysInputCode == GLFW_KEY_9) { return InputCode::KEYBOARD_9; }
    if (sysInputCode == GLFW_KEY_SEMICOLON) { return InputCode::KEYBOARD_SEMICOLON; }
    if (sysInputCode == GLFW_KEY_EQUAL) { return InputCode::KEYBOARD_EQUAL; }
    if (sysInputCode == GLFW_KEY_A) { return InputCode::KEYBOARD_A; }
    if (sysInputCode == GLFW_KEY_B) { return InputCode::KEYBOARD_B; }
    if (sysInputCode == GLFW_KEY_C) { return InputCode::KEYBOARD_C; }
    if (sysInputCode == GLFW_KEY_D) { return InputCode::KEYBOARD_D; }
    if (sysInputCode == GLFW_KEY_E) { return InputCode::KEYBOARD_E; }
    if (sysInputCode == GLFW_KEY_F) { return InputCode::KEYBOARD_F; }
    if (sysInputCode == GLFW_KEY_G) { return InputCode::KEYBOARD_G; }
    if (sysInputCode == GLFW_KEY_H) { return InputCode::KEYBOARD_H; }
    if (sysInputCode == GLFW_KEY_I) { return InputCode::KEYBOARD_I; }
    if (sysInputCode == GLFW_KEY_J) { return InputCode::KEYBOARD_J; }
    if (sysInputCode == GLFW_KEY_K) { return InputCode::KEYBOARD_K; }
    if (sysInputCode == GLFW_KEY_L) { return InputCode::KEYBOARD_L; }
    if (sysInputCode == GLFW_KEY_M) { return InputCode::KEYBOARD_M; }
    if (sysInputCode == GLFW_KEY_N) { return InputCode::KEYBOARD_N; }
    if (sysInputCode == GLFW_KEY_O) { return InputCode::KEYBOARD_O; }
    if (sysInputCode == GLFW_KEY_P) { return InputCode::KEYBOARD_P; }
    if (sysInputCode == GLFW_KEY_Q) { return InputCode::KEYBOARD_Q; }
    if (sysInputCode == GLFW_KEY_R) { return InputCode::KEYBOARD_R; }
    if (sysInputCode == GLFW_KEY_S) { return InputCode::KEYBOARD_S; }
    if (sysInputCode == GLFW_KEY_T) { return InputCode::KEYBOARD_T; }
    if (sysInputCode == GLFW_KEY_U) { return InputCode::KEYBOARD_U; }
    if (sysInputCode == GLFW_KEY_V) { return InputCode::KEYBOARD_V; }
    if (sysInputCode == GLFW_KEY_W) { return InputCode::KEYBOARD_W; }
    if (sysInputCode == GLFW_KEY_X) { return InputCode::KEYBOARD_X; }
    if (sysInputCode == GLFW_KEY_Y) { return InputCode::KEYBOARD_Y; }
    if (sysInputCode == GLFW_KEY_Z) { return InputCode::KEYBOARD_Z; }
    if (sysInputCode == GLFW_KEY_LEFT_BRACKET) { return InputCode::KEYBOARD_LEFT_BRACKET; }
    if (sysInputCode == GLFW_KEY_BACKSLASH) { return InputCode::KEYBOARD_BACKSLASH; }
    if (sysInputCode == GLFW_KEY_RIGHT_BRACKET) { return InputCode::KEYBOARD_RIGHT_BRACKET; }
    if (sysInputCode == GLFW_KEY_GRAVE_ACCENT) { return InputCode::KEYBOARD_GRAVE_ACCENT; }
    if (sysInputCode == GLFW_KEY_WORLD_1) { return InputCode::KEYBOARD_WORLD_1; }
    if (sysInputCode == GLFW_KEY_WORLD_2) { return InputCode::KEYBOARD_WORLD_2; }
    if (sysInputCode == GLFW_KEY_ESCAPE) { return InputCode::KEYBOARD_ESCAPE; }
    if (sysInputCode == GLFW_KEY_ENTER) { return InputCode::KEYBOARD_ENTER; }
    if (sysInputCode == GLFW_KEY_TAB) { return InputCode::KEYBOARD_TAB; }
    if (sysInputCode == GLFW_KEY_BACKSPACE) { return InputCode::KEYBOARD_BACKSPACE; }
    if (sysInputCode == GLFW_KEY_INSERT) { return InputCode::KEYBOARD_INSERT; }
    if (sysInputCode == GLFW_KEY_DELETE) { return InputCode::KEYBOARD_DELETE; }
    if (sysInputCode == GLFW_KEY_RIGHT) { return InputCode::KEYBOARD_RIGHT; }
    if (sysInputCode == GLFW_KEY_LEFT) { return InputCode::KEYBOARD_LEFT; }
    if (sysInputCode == GLFW_KEY_DOWN) { return InputCode::KEYBOARD_DOWN; }
    if (sysInputCode == GLFW_KEY_UP) { return InputCode::KEYBOARD_UP; }
    if (sysInputCode == GLFW_KEY_PAGE_UP) { return InputCode::KEYBOARD_PAGE_UP; }
    if (sysInputCode == GLFW_KEY_PAGE_DOWN) { return InputCode::KEYBOARD_PAGE_DOWN; }
    if (sysInputCode == GLFW_KEY_HOME) { return InputCode::KEYBOARD_HOME; }
    if (sysInputCode == GLFW_KEY_END) { return InputCode::KEYBOARD_END; }
    if (sysInputCode == GLFW_KEY_CAPS_LOCK) { return InputCode::KEYBOARD_CAPS_LOCK; }
    if (sysInputCode == GLFW_KEY_SCROLL_LOCK) { return InputCode::KEYBOARD_SCROLL_LOCK; }
    if (sysInputCode == GLFW_KEY_NUM_LOCK) { return InputCode::KEYBOARD_NUM_LOCK; }
    if (sysInputCode == GLFW_KEY_PRINT_SCREEN) { return InputCode::KEYBOARD_PRINT_SCREEN; }
    if (sysInputCode == GLFW_KEY_PAUSE) { return InputCode::KEYBOARD_PAUSE; }
    if (sysInputCode == GLFW_KEY_F1) { return InputCode::KEYBOARD_F1; }
    if (sysInputCode == GLFW_KEY_F2) { return InputCode::KEYBOARD_F2; }
    if (sysInputCode == GLFW_KEY_F3) { return InputCode::KEYBOARD_F3; }
    if (sysInputCode == GLFW_KEY_F4) { return InputCode::KEYBOARD_F4; }
    if (sysInputCode == GLFW_KEY_F5) { return InputCode::KEYBOARD_F5; }
    if (sysInputCode == GLFW_KEY_F6) { return InputCode::KEYBOARD_F6; }
    if (sysInputCode == GLFW_KEY_F7) { return InputCode::KEYBOARD_F7; }
    if (sysInputCode == GLFW_KEY_F8) { return InputCode::KEYBOARD_F8; }
    if (sysInputCode == GLFW_KEY_F9) { return InputCode::KEYBOARD_F9; }
    if (sysInputCode == GLFW_KEY_F10) { return InputCode::KEYBOARD_F10; }
    if (sysInputCode == GLFW_KEY_F11) { return InputCode::KEYBOARD_F11; }
    if (sysInputCode == GLFW_KEY_F12) { return InputCode::KEYBOARD_F12; }
    if (sysInputCode == GLFW_KEY_F13) { return InputCode::KEYBOARD_F13; }
    if (sysInputCode == GLFW_KEY_F14) { return InputCode::KEYBOARD_F14; }
    if (sysInputCode == GLFW_KEY_F15) { return InputCode::KEYBOARD_F15; }
    if (sysInputCode == GLFW_KEY_F16) { return InputCode::KEYBOARD_F16; }
    if (sysInputCode == GLFW_KEY_F17) { return InputCode::KEYBOARD_F17; }
    if (sysInputCode == GLFW_KEY_F18) { return InputCode::KEYBOARD_F18; }
    if (sysInputCode == GLFW_KEY_F19) { return InputCode::KEYBOARD_F19; }
    if (sysInputCode == GLFW_KEY_F20) { return InputCode::KEYBOARD_F20; }
    if (sysInputCode == GLFW_KEY_F21) { return InputCode::KEYBOARD_F21; }
    if (sysInputCode == GLFW_KEY_F22) { return InputCode::KEYBOARD_F22; }
    if (sysInputCode == GLFW_KEY_F23) { return InputCode::KEYBOARD_F23; }
    if (sysInputCode == GLFW_KEY_F24) { return InputCode::KEYBOARD_F24; }
    if (sysInputCode == GLFW_KEY_F25) { return InputCode::KEYBOARD_F25; }
    if (sysInputCode == GLFW_KEY_KP_0) { return InputCode::KEYBOARD_KP_0; }
    if (sysInputCode == GLFW_KEY_KP_1) { return InputCode::KEYBOARD_KP_1; }
    if (sysInputCode == GLFW_KEY_KP_2) { return InputCode::KEYBOARD_KP_2; }
    if (sysInputCode == GLFW_KEY_KP_3) { return InputCode::KEYBOARD_KP_3; }
    if (sysInputCode == GLFW_KEY_KP_4) { return InputCode::KEYBOARD_KP_4; }
    if (sysInputCode == GLFW_KEY_KP_5) { return InputCode::KEYBOARD_KP_5; }
    if (sysInputCode == GLFW_KEY_KP_6) { return InputCode::KEYBOARD_KP_6; }
    if (sysInputCode == GLFW_KEY_KP_7) { return InputCode::KEYBOARD_KP_7; }
    if (sysInputCode == GLFW_KEY_KP_8) { return InputCode::KEYBOARD_KP_8; }
    if (sysInputCode == GLFW_KEY_KP_9) { return InputCode::KEYBOARD_KP_9; }
    if (sysInputCode == GLFW_KEY_KP_DECIMAL) { return InputCode::KEYBOARD_KP_DECIMAL; }
    if (sysInputCode == GLFW_KEY_KP_DIVIDE) { return InputCode::KEYBOARD_KP_DIVIDE; }
    if (sysInputCode == GLFW_KEY_KP_MULTIPLY) { return InputCode::KEYBOARD_KP_MULTIPLY; }
    if (sysInputCode == GLFW_KEY_KP_SUBTRACT) { return InputCode::KEYBOARD_KP_SUBTRACT; }
    if (sysInputCode == GLFW_KEY_KP_ADD) { return InputCode::KEYBOARD_KP_ADD; }
    if (sysInputCode == GLFW_KEY_KP_ENTER) { return InputCode::KEYBOARD_KP_ENTER; }
    if (sysInputCode == GLFW_KEY_KP_EQUAL) { return InputCode::KEYBOARD_KP_EQUAL; }
    if (sysInputCode == GLFW_KEY_LEFT_SHIFT) { return InputCode::KEYBOARD_LEFT_SHIFT; }
    if (sysInputCode == GLFW_KEY_LEFT_CONTROL) { return InputCode::KEYBOARD_LEFT_CONTROL; }
    if (sysInputCode == GLFW_KEY_LEFT_ALT) { return InputCode::KEYBOARD_LEFT_ALT; }
    if (sysInputCode == GLFW_KEY_LEFT_SUPER) { return InputCode::KEYBOARD_LEFT_SUPER; }
    if (sysInputCode == GLFW_KEY_RIGHT_SHIFT) { return InputCode::KEYBOARD_RIGHT_SHIFT; }
    if (sysInputCode == GLFW_KEY_RIGHT_CONTROL) { return InputCode::KEYBOARD_RIGHT_CONTROL; }
    if (sysInputCode == GLFW_KEY_RIGHT_ALT) { return InputCode::KEYBOARD_RIGHT_ALT; }
    if (sysInputCode == GLFW_KEY_RIGHT_SUPER) { return InputCode::KEYBOARD_RIGHT_SUPER; }
    if (sysInputCode == GLFW_KEY_MENU) { return InputCode::KEYBOARD_MENU; }
    return InputCode::NONE;
}

InputCode sysInputMouseCode2GHCode(int sysInputCode) {
    if (sysInputCode == GLFW_MOUSE_BUTTON_1) { return InputCode::MOUSE_BUTTON_1; }
    if (sysInputCode == GLFW_MOUSE_BUTTON_2) { return InputCode::MOUSE_BUTTON_2; }
    if (sysInputCode == GLFW_MOUSE_BUTTON_3) { return InputCode::MOUSE_BUTTON_3; }
    if (sysInputCode == GLFW_MOUSE_BUTTON_4) { return InputCode::MOUSE_BUTTON_4; }
    if (sysInputCode == GLFW_MOUSE_BUTTON_5) { return InputCode::MOUSE_BUTTON_5; }
    if (sysInputCode == GLFW_MOUSE_BUTTON_6) { return InputCode::MOUSE_BUTTON_6; }
    if (sysInputCode == GLFW_MOUSE_BUTTON_7) { return InputCode::MOUSE_BUTTON_7; }
    if (sysInputCode == GLFW_MOUSE_BUTTON_8) { return InputCode::MOUSE_BUTTON_8; }
    return InputCode::NONE;
}

}

#endif //GANESHENGINE_GHINPUTGLFWUTILS_H
