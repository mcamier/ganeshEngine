#include <input/ghInputUtils.hpp>

namespace ganeshEngine {

namespace inputDetails {

template<>
const char *toString<InputSource>(InputSource value) {
	if (value == InputSource::MOUSE) return sourceMouse;
	if (value == InputSource::KEYBOARD) return sourceKeyboard;
	if (value == InputSource::DEVICE) return sourceDevice;
	return "Undefined";
}

template<>
const char *toString<InputType>(InputType value) {
	if (value == InputType::BUTTON_UP) return typeUp;
	if (value == InputType::BUTTON_PRESS) return typePress;
	if (value == InputType::BUTTON_DOWN) return typeDown;
	if (value == InputType::BUTTON_RELEASE) return typeRelease;
	if (value == InputType::AXIS) return typeAxis;
	return "Undefined";
}

template<>
const char *toString<InputCode>(InputCode value) {
	if (value == InputCode::KEYBOARD_F1) return inputDetails::KEYBOARD_F1;
	if (value == InputCode::KEYBOARD_F2) return inputDetails::KEYBOARD_F2;
	if (value == InputCode::KEYBOARD_F3) return inputDetails::KEYBOARD_F3;
	if (value == InputCode::KEYBOARD_F4) return inputDetails::KEYBOARD_F4;
	if (value == InputCode::KEYBOARD_F5) return inputDetails::KEYBOARD_F5;
	if (value == InputCode::KEYBOARD_F6) return inputDetails::KEYBOARD_F6;
	if (value == InputCode::KEYBOARD_F7) return inputDetails::KEYBOARD_F7;
	if (value == InputCode::KEYBOARD_F8) return inputDetails::KEYBOARD_F8;
	if (value == InputCode::KEYBOARD_F9) return inputDetails::KEYBOARD_F9;
	if (value == InputCode::KEYBOARD_F10) return inputDetails::KEYBOARD_F10;
	if (value == InputCode::KEYBOARD_F11) return inputDetails::KEYBOARD_F11;
	if (value == InputCode::KEYBOARD_F12) return inputDetails::KEYBOARD_F12;
	if (value == InputCode::KEYBOARD_F13) return inputDetails::KEYBOARD_F13;
	if (value == InputCode::KEYBOARD_F14) return inputDetails::KEYBOARD_F14;
	if (value == InputCode::KEYBOARD_F15) return inputDetails::KEYBOARD_F15;
	if (value == InputCode::KEYBOARD_F16) return inputDetails::KEYBOARD_F16;
	if (value == InputCode::KEYBOARD_F17) return inputDetails::KEYBOARD_F17;
	if (value == InputCode::KEYBOARD_F18) return inputDetails::KEYBOARD_F18;
	if (value == InputCode::KEYBOARD_F19) return inputDetails::KEYBOARD_F19;
	if (value == InputCode::KEYBOARD_F20) return inputDetails::KEYBOARD_F20;
	if (value == InputCode::KEYBOARD_F21) return inputDetails::KEYBOARD_F21;
	if (value == InputCode::KEYBOARD_F22) return inputDetails::KEYBOARD_F22;
	if (value == InputCode::KEYBOARD_F23) return inputDetails::KEYBOARD_F23;
	if (value == InputCode::KEYBOARD_F24) return inputDetails::KEYBOARD_F24;
	if (value == InputCode::KEYBOARD_F25) return inputDetails::KEYBOARD_F25;
	if (value == InputCode::KEYBOARD_SPACE) return inputDetails::KEYBOARD_SPACE;
	if (value == InputCode::KEYBOARD_APOSTROPHE) return inputDetails::KEYBOARD_APOSTROPHE;
	if (value == InputCode::KEYBOARD_COMMA) return inputDetails::KEYBOARD_COMMA;
	if (value == InputCode::KEYBOARD_MINUS) return inputDetails::KEYBOARD_MINUS;
	if (value == InputCode::KEYBOARD_PERIOD) return inputDetails::KEYBOARD_PERIOD;
	if (value == InputCode::KEYBOARD_SLASH) return inputDetails::KEYBOARD_SLASH;
	if (value == InputCode::KEYBOARD_0) return inputDetails::KEYBOARD_0;
	if (value == InputCode::KEYBOARD_1) return inputDetails::KEYBOARD_1;
	if (value == InputCode::KEYBOARD_2) return inputDetails::KEYBOARD_2;
	if (value == InputCode::KEYBOARD_3) return inputDetails::KEYBOARD_3;
	if (value == InputCode::KEYBOARD_4) return inputDetails::KEYBOARD_4;
	if (value == InputCode::KEYBOARD_5) return inputDetails::KEYBOARD_5;
	if (value == InputCode::KEYBOARD_6) return inputDetails::KEYBOARD_6;
	if (value == InputCode::KEYBOARD_7) return inputDetails::KEYBOARD_7;
	if (value == InputCode::KEYBOARD_8) return inputDetails::KEYBOARD_8;
	if (value == InputCode::KEYBOARD_9) return inputDetails::KEYBOARD_9;
	if (value == InputCode::KEYBOARD_KP_0) return inputDetails::KEYBOARD_KP_0;
	if (value == InputCode::KEYBOARD_KP_1) return inputDetails::KEYBOARD_KP_1;
	if (value == InputCode::KEYBOARD_KP_2) return inputDetails::KEYBOARD_KP_2;
	if (value == InputCode::KEYBOARD_KP_3) return inputDetails::KEYBOARD_KP_3;
	if (value == InputCode::KEYBOARD_KP_4) return inputDetails::KEYBOARD_KP_4;
	if (value == InputCode::KEYBOARD_KP_5) return inputDetails::KEYBOARD_KP_5;
	if (value == InputCode::KEYBOARD_KP_6) return inputDetails::KEYBOARD_KP_6;
	if (value == InputCode::KEYBOARD_KP_7) return inputDetails::KEYBOARD_KP_7;
	if (value == InputCode::KEYBOARD_KP_8) return inputDetails::KEYBOARD_KP_8;
	if (value == InputCode::KEYBOARD_KP_9) return inputDetails::KEYBOARD_KP_9;
	if (value == InputCode::KEYBOARD_SEMICOLON) return inputDetails::KEYBOARD_SEMICOLON;
	if (value == InputCode::KEYBOARD_EQUAL) return inputDetails::KEYBOARD_EQUAL;
	if (value == InputCode::KEYBOARD_A) return inputDetails::KEYBOARD_A;
	if (value == InputCode::KEYBOARD_B) return inputDetails::KEYBOARD_B;
	if (value == InputCode::KEYBOARD_C) return inputDetails::KEYBOARD_C;
	if (value == InputCode::KEYBOARD_D) return inputDetails::KEYBOARD_D;
	if (value == InputCode::KEYBOARD_E) return inputDetails::KEYBOARD_E;
	if (value == InputCode::KEYBOARD_F) return inputDetails::KEYBOARD_F;
	if (value == InputCode::KEYBOARD_G) return inputDetails::KEYBOARD_G;
	if (value == InputCode::KEYBOARD_H) return inputDetails::KEYBOARD_H;
	if (value == InputCode::KEYBOARD_I) return inputDetails::KEYBOARD_I;
	if (value == InputCode::KEYBOARD_J) return inputDetails::KEYBOARD_J;
	if (value == InputCode::KEYBOARD_K) return inputDetails::KEYBOARD_K;
	if (value == InputCode::KEYBOARD_L) return inputDetails::KEYBOARD_L;
	if (value == InputCode::KEYBOARD_M) return inputDetails::KEYBOARD_M;
	if (value == InputCode::KEYBOARD_N) return inputDetails::KEYBOARD_N;
	if (value == InputCode::KEYBOARD_O) return inputDetails::KEYBOARD_O;
	if (value == InputCode::KEYBOARD_P) return inputDetails::KEYBOARD_P;
	if (value == InputCode::KEYBOARD_Q) return inputDetails::KEYBOARD_Q;
	if (value == InputCode::KEYBOARD_R) return inputDetails::KEYBOARD_R;
	if (value == InputCode::KEYBOARD_S) return inputDetails::KEYBOARD_S;
	if (value == InputCode::KEYBOARD_T) return inputDetails::KEYBOARD_T;
	if (value == InputCode::KEYBOARD_U) return inputDetails::KEYBOARD_U;
	if (value == InputCode::KEYBOARD_V) return inputDetails::KEYBOARD_V;
	if (value == InputCode::KEYBOARD_W) return inputDetails::KEYBOARD_W;
	if (value == InputCode::KEYBOARD_X) return inputDetails::KEYBOARD_X;
	if (value == InputCode::KEYBOARD_Y) return inputDetails::KEYBOARD_Y;
	if (value == InputCode::KEYBOARD_Z) return inputDetails::KEYBOARD_Z;
	if (value == InputCode::KEYBOARD_LEFT_BRACKET) return inputDetails::KEYBOARD_LEFT_BRACKET;
	if (value == InputCode::KEYBOARD_BACKSLASH) return inputDetails::KEYBOARD_BACKSLASH;
	if (value == InputCode::KEYBOARD_RIGHT_BRACKET) return inputDetails::KEYBOARD_RIGHT_BRACKET;
	if (value == InputCode::KEYBOARD_GRAVE_ACCENT) return inputDetails::KEYBOARD_GRAVE_ACCENT;
	if (value == InputCode::KEYBOARD_WORLD_1) return inputDetails::KEYBOARD_WORLD_1;
	if (value == InputCode::KEYBOARD_WORLD_2) return inputDetails::KEYBOARD_WORLD_2;
	if (value == InputCode::KEYBOARD_ESCAPE) return inputDetails::KEYBOARD_ESCAPE;
	if (value == InputCode::KEYBOARD_ENTER) return inputDetails::KEYBOARD_ENTER;
	if (value == InputCode::KEYBOARD_TAB) return inputDetails::KEYBOARD_TAB;
	if (value == InputCode::KEYBOARD_BACKSPACE) return inputDetails::KEYBOARD_BACKSPACE;
	if (value == InputCode::KEYBOARD_INSERT) return inputDetails::KEYBOARD_INSERT;
	if (value == InputCode::KEYBOARD_DELETE) return inputDetails::KEYBOARD_DELETE;
	if (value == InputCode::KEYBOARD_RIGHT) return inputDetails::KEYBOARD_RIGHT;
	if (value == InputCode::KEYBOARD_LEFT) return inputDetails::KEYBOARD_LEFT;
	if (value == InputCode::KEYBOARD_DOWN) return inputDetails::KEYBOARD_DOWN;
	if (value == InputCode::KEYBOARD_UP) return inputDetails::KEYBOARD_UP;
	if (value == InputCode::KEYBOARD_PAGE_UP) return inputDetails::KEYBOARD_PAGE_UP;
	if (value == InputCode::KEYBOARD_PAGE_DOWN) return inputDetails::KEYBOARD_PAGE_DOWN;
	if (value == InputCode::KEYBOARD_HOME) return inputDetails::KEYBOARD_HOME;
	if (value == InputCode::KEYBOARD_END) return inputDetails::KEYBOARD_END;
	if (value == InputCode::KEYBOARD_CAPS_LOCK) return inputDetails::KEYBOARD_CAPS_LOCK;
	if (value == InputCode::KEYBOARD_SCROLL_LOCK) return inputDetails::KEYBOARD_SCROLL_LOCK;
	if (value == InputCode::KEYBOARD_NUM_LOCK) return inputDetails::KEYBOARD_NUM_LOCK;
	if (value == InputCode::KEYBOARD_PRINT_SCREEN) return inputDetails::KEYBOARD_PRINT_SCREEN;
	if (value == InputCode::KEYBOARD_PAUSE) return inputDetails::KEYBOARD_PAUSE;
	if (value == InputCode::KEYBOARD_KP_DECIMAL) return inputDetails::KEYBOARD_KP_DECIMAL;
	if (value == InputCode::KEYBOARD_KP_DIVIDE) return inputDetails::KEYBOARD_KP_DIVIDE;
	if (value == InputCode::KEYBOARD_KP_MULTIPLY) return inputDetails::KEYBOARD_KP_MULTIPLY;
	if (value == InputCode::KEYBOARD_KP_SUBTRACT) return inputDetails::KEYBOARD_KP_SUBTRACT;
	if (value == InputCode::KEYBOARD_KP_ADD) return inputDetails::KEYBOARD_KP_ADD;
	if (value == InputCode::KEYBOARD_KP_ENTER) return inputDetails::KEYBOARD_KP_ENTER;
	if (value == InputCode::KEYBOARD_KP_EQUAL) return inputDetails::KEYBOARD_KP_EQUAL;
	if (value == InputCode::KEYBOARD_LEFT_SHIFT) return inputDetails::KEYBOARD_LEFT_SHIFT;
	if (value == InputCode::KEYBOARD_LEFT_CONTROL) return inputDetails::KEYBOARD_LEFT_CONTROL;
	if (value == InputCode::KEYBOARD_LEFT_ALT) return inputDetails::KEYBOARD_LEFT_ALT;
	if (value == InputCode::KEYBOARD_LEFT_SUPER) return inputDetails::KEYBOARD_LEFT_SUPER;
	if (value == InputCode::KEYBOARD_RIGHT_SHIFT) return inputDetails::KEYBOARD_RIGHT_SHIFT;
	if (value == InputCode::KEYBOARD_RIGHT_CONTROL) return inputDetails::KEYBOARD_RIGHT_CONTROL;
	if (value == InputCode::KEYBOARD_RIGHT_ALT) return inputDetails::KEYBOARD_RIGHT_ALT;
	if (value == InputCode::KEYBOARD_RIGHT_SUPER) return inputDetails::KEYBOARD_RIGHT_SUPER;
	if (value == InputCode::KEYBOARD_MENU) return inputDetails::KEYBOARD_MENU;
	if (value == InputCode::MOUSE_BUTTON_1) return inputDetails::MOUSE_BUTTON_1;
	if (value == InputCode::MOUSE_BUTTON_2) return inputDetails::MOUSE_BUTTON_2;
	if (value == InputCode::MOUSE_BUTTON_3) return inputDetails::MOUSE_BUTTON_3;
	if (value == InputCode::MOUSE_BUTTON_4) return inputDetails::MOUSE_BUTTON_4;
	if (value == InputCode::MOUSE_BUTTON_5) return inputDetails::MOUSE_BUTTON_5;
	if (value == InputCode::MOUSE_BUTTON_6) return inputDetails::MOUSE_BUTTON_6;
	if (value == InputCode::MOUSE_BUTTON_7) return inputDetails::MOUSE_BUTTON_7;
	if (value == InputCode::MOUSE_BUTTON_8) return inputDetails::MOUSE_BUTTON_8;
	if (value == InputCode::MOUSE_LEFT) return inputDetails::MOUSE_LEFT;
	if (value == InputCode::MOUSE_RIGHT) return inputDetails::MOUSE_RIGHT;
	if (value == InputCode::MOUSE_MIDDLE) return inputDetails::MOUSE_MIDDLE;
	if (value == InputCode::XBOX_CONTROLLER_A) return inputDetails::XBOX_CONTROLLER_A;
	if (value == InputCode::XBOX_CONTROLLER_B) return inputDetails::XBOX_CONTROLLER_B;
	if (value == InputCode::XBOX_CONTROLLER_X) return inputDetails::XBOX_CONTROLLER_X;
	if (value == InputCode::XBOX_CONTROLLER_Y) return inputDetails::XBOX_CONTROLLER_Y;
	if (value == InputCode::XBOX_CONTROLLER_START) return inputDetails::XBOX_CONTROLLER_START;
	if (value == InputCode::XBOX_CONTROLLER_SELECT) return inputDetails::XBOX_CONTROLLER_SELECT;
	if (value == InputCode::XBOX_CONTROLLER_MENU) return inputDetails::XBOX_CONTROLLER_MENU;
    if (value == InputCode::XBOX_CONTROLLER_RS) return inputDetails::XBOX_CONTROLLER_RS;
    if (value == InputCode::XBOX_CONTROLLER_LS) return inputDetails::XBOX_CONTROLLER_LS;
    if (value == InputCode::XBOX_CONTROLLER_RB) return inputDetails::XBOX_CONTROLLER_RB;
    if (value == InputCode::XBOX_CONTROLLER_LB) return inputDetails::XBOX_CONTROLLER_LB;
	if (value == InputCode::XBOX_CONTROLLER_UP) return inputDetails::XBOX_CONTROLLER_UP;
	if (value == InputCode::XBOX_CONTROLLER_DOWN) return inputDetails::XBOX_CONTROLLER_DOWN;
	if (value == InputCode::XBOX_CONTROLLER_LEFT) return inputDetails::XBOX_CONTROLLER_LEFT;
	if (value == InputCode::XBOX_CONTROLLER_RIGHT) return inputDetails::XBOX_CONTROLLER_RIGHT;
	if (value == InputCode::XBOX_CONTROLLER_AXIS_LEFT_X) return inputDetails::XBOX_CONTROLLER_AXIS_LEFT_X;
	if (value == InputCode::XBOX_CONTROLLER_AXIS_LEFT_Y) return inputDetails::XBOX_CONTROLLER_AXIS_LEFT_Y;
	if (value == InputCode::XBOX_CONTROLLER_AXIS_RIGHT_X) return inputDetails::XBOX_CONTROLLER_AXIS_RIGHT_X;
	if (value == InputCode::XBOX_CONTROLLER_AXIS_RIGHT_Y) return inputDetails::XBOX_CONTROLLER_AXIS_RIGHT_Y;
	if (value == InputCode::XBOX_CONTROLLER_AXIS_RT) return inputDetails::XBOX_CONTROLLER_AXIS_RT;
	if (value == InputCode::XBOX_CONTROLLER_AXIS_LT) return inputDetails::XBOX_CONTROLLER_AXIS_LT;
	if (value == InputCode::UNSUPPORTED) return inputDetails::UNSUPPORTED;
	return inputDetails::UNSUPPORTED;
}

template<>
InputSource fromString<InputSource>(const char *value) {
	if (strcmp(value, sourceMouse) == 0) return InputSource::MOUSE;
	if (strcmp(value, sourceKeyboard) == 0) return InputSource::KEYBOARD;
	if (strcmp(value, sourceDevice) == 0) return InputSource::DEVICE;

}

template<>
InputType fromString<InputType>(const char *value) {
	if (strcmp(value, typeUp) == 0) return InputType::BUTTON_UP;
	if (strcmp(value, typePress) == 0) return InputType::BUTTON_PRESS;
	if (strcmp(value, typeDown) == 0) return InputType::BUTTON_DOWN;
	if (strcmp(value, typeRelease) == 0) return InputType::BUTTON_RELEASE;
	if (strcmp(value, typeAxis) == 0) return InputType::AXIS;
}

template<>
InputCode fromString<InputCode>(const char *value) {
	if (strcmp(value, inputDetails::KEYBOARD_F1) == 0) return InputCode::KEYBOARD_F1;
	if (strcmp(value, inputDetails::KEYBOARD_F2) == 0) return InputCode::KEYBOARD_F2;
	if (strcmp(value, inputDetails::KEYBOARD_F3) == 0) return InputCode::KEYBOARD_F3;
	if (strcmp(value, inputDetails::KEYBOARD_F4) == 0) return InputCode::KEYBOARD_F4;
	if (strcmp(value, inputDetails::KEYBOARD_F5) == 0) return InputCode::KEYBOARD_F5;
	if (strcmp(value, inputDetails::KEYBOARD_F6) == 0) return InputCode::KEYBOARD_F6;
	if (strcmp(value, inputDetails::KEYBOARD_F7) == 0) return InputCode::KEYBOARD_F7;
	if (strcmp(value, inputDetails::KEYBOARD_F8) == 0) return InputCode::KEYBOARD_F8;
	if (strcmp(value, inputDetails::KEYBOARD_F9) == 0) return InputCode::KEYBOARD_F9;
	if (strcmp(value, inputDetails::KEYBOARD_F10) == 0) return InputCode::KEYBOARD_F10;
	if (strcmp(value, inputDetails::KEYBOARD_F11) == 0) return InputCode::KEYBOARD_F11;
	if (strcmp(value, inputDetails::KEYBOARD_F12) == 0) return InputCode::KEYBOARD_F12;
	if (strcmp(value, inputDetails::KEYBOARD_F13) == 0) return InputCode::KEYBOARD_F13;
	if (strcmp(value, inputDetails::KEYBOARD_F14) == 0) return InputCode::KEYBOARD_F14;
	if (strcmp(value, inputDetails::KEYBOARD_F15) == 0) return InputCode::KEYBOARD_F15;
	if (strcmp(value, inputDetails::KEYBOARD_F16) == 0) return InputCode::KEYBOARD_F16;
	if (strcmp(value, inputDetails::KEYBOARD_F17) == 0) return InputCode::KEYBOARD_F17;
	if (strcmp(value, inputDetails::KEYBOARD_F18) == 0) return InputCode::KEYBOARD_F18;
	if (strcmp(value, inputDetails::KEYBOARD_F19) == 0) return InputCode::KEYBOARD_F19;
	if (strcmp(value, inputDetails::KEYBOARD_F20) == 0) return InputCode::KEYBOARD_F20;
	if (strcmp(value, inputDetails::KEYBOARD_F21) == 0) return InputCode::KEYBOARD_F21;
	if (strcmp(value, inputDetails::KEYBOARD_F22) == 0) return InputCode::KEYBOARD_F22;
	if (strcmp(value, inputDetails::KEYBOARD_F23) == 0) return InputCode::KEYBOARD_F23;
	if (strcmp(value, inputDetails::KEYBOARD_F24) == 0) return InputCode::KEYBOARD_F24;
	if (strcmp(value, inputDetails::KEYBOARD_F25) == 0) return InputCode::KEYBOARD_F25;
	if (strcmp(value, inputDetails::KEYBOARD_SPACE) == 0) return InputCode::KEYBOARD_SPACE;
	if (strcmp(value, inputDetails::KEYBOARD_APOSTROPHE) == 0) return InputCode::KEYBOARD_APOSTROPHE;
	if (strcmp(value, inputDetails::KEYBOARD_COMMA) == 0) return InputCode::KEYBOARD_COMMA;
	if (strcmp(value, inputDetails::KEYBOARD_MINUS) == 0) return InputCode::KEYBOARD_MINUS;
	if (strcmp(value, inputDetails::KEYBOARD_PERIOD) == 0) return InputCode::KEYBOARD_PERIOD;
	if (strcmp(value, inputDetails::KEYBOARD_SLASH) == 0) return InputCode::KEYBOARD_SLASH;
	if (strcmp(value, inputDetails::KEYBOARD_0) == 0) return InputCode::KEYBOARD_0;
	if (strcmp(value, inputDetails::KEYBOARD_1) == 0) return InputCode::KEYBOARD_1;
	if (strcmp(value, inputDetails::KEYBOARD_2) == 0) return InputCode::KEYBOARD_2;
	if (strcmp(value, inputDetails::KEYBOARD_3) == 0) return InputCode::KEYBOARD_3;
	if (strcmp(value, inputDetails::KEYBOARD_4) == 0) return InputCode::KEYBOARD_4;
	if (strcmp(value, inputDetails::KEYBOARD_5) == 0) return InputCode::KEYBOARD_5;
	if (strcmp(value, inputDetails::KEYBOARD_6) == 0) return InputCode::KEYBOARD_6;
	if (strcmp(value, inputDetails::KEYBOARD_7) == 0) return InputCode::KEYBOARD_7;
	if (strcmp(value, inputDetails::KEYBOARD_8) == 0) return InputCode::KEYBOARD_8;
	if (strcmp(value, inputDetails::KEYBOARD_9) == 0) return InputCode::KEYBOARD_9;
	if (strcmp(value, inputDetails::KEYBOARD_KP_0) == 0) return InputCode::KEYBOARD_KP_0;
	if (strcmp(value, inputDetails::KEYBOARD_KP_1) == 0) return InputCode::KEYBOARD_KP_1;
	if (strcmp(value, inputDetails::KEYBOARD_KP_2) == 0) return InputCode::KEYBOARD_KP_2;
	if (strcmp(value, inputDetails::KEYBOARD_KP_3) == 0) return InputCode::KEYBOARD_KP_3;
	if (strcmp(value, inputDetails::KEYBOARD_KP_4) == 0) return InputCode::KEYBOARD_KP_4;
	if (strcmp(value, inputDetails::KEYBOARD_KP_5) == 0) return InputCode::KEYBOARD_KP_5;
	if (strcmp(value, inputDetails::KEYBOARD_KP_6) == 0) return InputCode::KEYBOARD_KP_6;
	if (strcmp(value, inputDetails::KEYBOARD_KP_7) == 0) return InputCode::KEYBOARD_KP_7;
	if (strcmp(value, inputDetails::KEYBOARD_KP_8) == 0) return InputCode::KEYBOARD_KP_8;
	if (strcmp(value, inputDetails::KEYBOARD_KP_9) == 0) return InputCode::KEYBOARD_KP_9;
	if (strcmp(value, inputDetails::KEYBOARD_SEMICOLON) == 0) return InputCode::KEYBOARD_SEMICOLON;
	if (strcmp(value, inputDetails::KEYBOARD_EQUAL) == 0) return InputCode::KEYBOARD_EQUAL;
	if (strcmp(value, inputDetails::KEYBOARD_A) == 0) return InputCode::KEYBOARD_A;
	if (strcmp(value, inputDetails::KEYBOARD_B) == 0) return InputCode::KEYBOARD_B;
	if (strcmp(value, inputDetails::KEYBOARD_C) == 0) return InputCode::KEYBOARD_C;
	if (strcmp(value, inputDetails::KEYBOARD_D) == 0) return InputCode::KEYBOARD_D;
	if (strcmp(value, inputDetails::KEYBOARD_E) == 0) return InputCode::KEYBOARD_E;
	if (strcmp(value, inputDetails::KEYBOARD_F) == 0) return InputCode::KEYBOARD_F;
	if (strcmp(value, inputDetails::KEYBOARD_G) == 0) return InputCode::KEYBOARD_G;
	if (strcmp(value, inputDetails::KEYBOARD_H) == 0) return InputCode::KEYBOARD_H;
	if (strcmp(value, inputDetails::KEYBOARD_I) == 0) return InputCode::KEYBOARD_I;
	if (strcmp(value, inputDetails::KEYBOARD_J) == 0) return InputCode::KEYBOARD_J;
	if (strcmp(value, inputDetails::KEYBOARD_K) == 0) return InputCode::KEYBOARD_K;
	if (strcmp(value, inputDetails::KEYBOARD_L) == 0) return InputCode::KEYBOARD_L;
	if (strcmp(value, inputDetails::KEYBOARD_M) == 0) return InputCode::KEYBOARD_M;
	if (strcmp(value, inputDetails::KEYBOARD_N) == 0) return InputCode::KEYBOARD_N;
	if (strcmp(value, inputDetails::KEYBOARD_O) == 0) return InputCode::KEYBOARD_O;
	if (strcmp(value, inputDetails::KEYBOARD_P) == 0) return InputCode::KEYBOARD_P;
	if (strcmp(value, inputDetails::KEYBOARD_Q) == 0) return InputCode::KEYBOARD_Q;
	if (strcmp(value, inputDetails::KEYBOARD_R) == 0) return InputCode::KEYBOARD_R;
	if (strcmp(value, inputDetails::KEYBOARD_S) == 0) return InputCode::KEYBOARD_S;
	if (strcmp(value, inputDetails::KEYBOARD_T) == 0) return InputCode::KEYBOARD_T;
	if (strcmp(value, inputDetails::KEYBOARD_U) == 0) return InputCode::KEYBOARD_U;
	if (strcmp(value, inputDetails::KEYBOARD_V) == 0) return InputCode::KEYBOARD_V;
	if (strcmp(value, inputDetails::KEYBOARD_W) == 0) return InputCode::KEYBOARD_W;
	if (strcmp(value, inputDetails::KEYBOARD_X) == 0) return InputCode::KEYBOARD_X;
	if (strcmp(value, inputDetails::KEYBOARD_Y) == 0) return InputCode::KEYBOARD_Y;
	if (strcmp(value, inputDetails::KEYBOARD_Z) == 0) return InputCode::KEYBOARD_Z;
	if (strcmp(value, inputDetails::KEYBOARD_LEFT_BRACKET) == 0) return InputCode::KEYBOARD_LEFT_BRACKET;
	if (strcmp(value, inputDetails::KEYBOARD_BACKSLASH) == 0) return InputCode::KEYBOARD_BACKSLASH;
	if (strcmp(value, inputDetails::KEYBOARD_RIGHT_BRACKET) == 0) return InputCode::KEYBOARD_RIGHT_BRACKET;
	if (strcmp(value, inputDetails::KEYBOARD_GRAVE_ACCENT) == 0) return InputCode::KEYBOARD_GRAVE_ACCENT;
	if (strcmp(value, inputDetails::KEYBOARD_WORLD_1) == 0) return InputCode::KEYBOARD_WORLD_1;
	if (strcmp(value, inputDetails::KEYBOARD_WORLD_2) == 0) return InputCode::KEYBOARD_WORLD_2;
	if (strcmp(value, inputDetails::KEYBOARD_ESCAPE) == 0) return InputCode::KEYBOARD_ESCAPE;
	if (strcmp(value, inputDetails::KEYBOARD_ENTER) == 0) return InputCode::KEYBOARD_ENTER;
	if (strcmp(value, inputDetails::KEYBOARD_TAB) == 0) return InputCode::KEYBOARD_TAB;
	if (strcmp(value, inputDetails::KEYBOARD_BACKSPACE) == 0) return InputCode::KEYBOARD_BACKSPACE;
	if (strcmp(value, inputDetails::KEYBOARD_INSERT) == 0) return InputCode::KEYBOARD_INSERT;
	if (strcmp(value, inputDetails::KEYBOARD_DELETE) == 0) return InputCode::KEYBOARD_DELETE;
	if (strcmp(value, inputDetails::KEYBOARD_RIGHT) == 0) return InputCode::KEYBOARD_RIGHT;
	if (strcmp(value, inputDetails::KEYBOARD_LEFT) == 0) return InputCode::KEYBOARD_LEFT;
	if (strcmp(value, inputDetails::KEYBOARD_DOWN) == 0) return InputCode::KEYBOARD_DOWN;
	if (strcmp(value, inputDetails::KEYBOARD_UP) == 0) return InputCode::KEYBOARD_UP;
	if (strcmp(value, inputDetails::KEYBOARD_PAGE_UP) == 0) return InputCode::KEYBOARD_PAGE_UP;
	if (strcmp(value, inputDetails::KEYBOARD_PAGE_DOWN) == 0) return InputCode::KEYBOARD_PAGE_DOWN;
	if (strcmp(value, inputDetails::KEYBOARD_HOME) == 0) return InputCode::KEYBOARD_HOME;
	if (strcmp(value, inputDetails::KEYBOARD_END) == 0) return InputCode::KEYBOARD_END;
	if (strcmp(value, inputDetails::KEYBOARD_CAPS_LOCK) == 0) return InputCode::KEYBOARD_CAPS_LOCK;
	if (strcmp(value, inputDetails::KEYBOARD_SCROLL_LOCK) == 0) return InputCode::KEYBOARD_SCROLL_LOCK;
	if (strcmp(value, inputDetails::KEYBOARD_NUM_LOCK) == 0) return InputCode::KEYBOARD_NUM_LOCK;
	if (strcmp(value, inputDetails::KEYBOARD_PRINT_SCREEN) == 0) return InputCode::KEYBOARD_PRINT_SCREEN;
	if (strcmp(value, inputDetails::KEYBOARD_PAUSE) == 0) return InputCode::KEYBOARD_PAUSE;
	if (strcmp(value, inputDetails::KEYBOARD_KP_DECIMAL) == 0) return InputCode::KEYBOARD_KP_DECIMAL;
	if (strcmp(value, inputDetails::KEYBOARD_KP_DIVIDE) == 0) return InputCode::KEYBOARD_KP_DIVIDE;
	if (strcmp(value, inputDetails::KEYBOARD_KP_MULTIPLY) == 0) return InputCode::KEYBOARD_KP_MULTIPLY;
	if (strcmp(value, inputDetails::KEYBOARD_KP_SUBTRACT) == 0) return InputCode::KEYBOARD_KP_SUBTRACT;
	if (strcmp(value, inputDetails::KEYBOARD_KP_ADD) == 0) return InputCode::KEYBOARD_KP_ADD;
	if (strcmp(value, inputDetails::KEYBOARD_KP_ENTER) == 0) return InputCode::KEYBOARD_KP_ENTER;
	if (strcmp(value, inputDetails::KEYBOARD_KP_EQUAL) == 0) return InputCode::KEYBOARD_KP_EQUAL;
	if (strcmp(value, inputDetails::KEYBOARD_LEFT_SHIFT) == 0) return InputCode::KEYBOARD_LEFT_SHIFT;
	if (strcmp(value, inputDetails::KEYBOARD_LEFT_CONTROL) == 0) return InputCode::KEYBOARD_LEFT_CONTROL;
	if (strcmp(value, inputDetails::KEYBOARD_LEFT_ALT) == 0) return InputCode::KEYBOARD_LEFT_ALT;
	if (strcmp(value, inputDetails::KEYBOARD_LEFT_SUPER) == 0) return InputCode::KEYBOARD_LEFT_SUPER;
	if (strcmp(value, inputDetails::KEYBOARD_RIGHT_SHIFT) == 0) return InputCode::KEYBOARD_RIGHT_SHIFT;
	if (strcmp(value, inputDetails::KEYBOARD_RIGHT_CONTROL) == 0) return InputCode::KEYBOARD_RIGHT_CONTROL;
	if (strcmp(value, inputDetails::KEYBOARD_RIGHT_ALT) == 0) return InputCode::KEYBOARD_RIGHT_ALT;
	if (strcmp(value, inputDetails::KEYBOARD_RIGHT_SUPER) == 0) return InputCode::KEYBOARD_RIGHT_SUPER;
	if (strcmp(value, inputDetails::KEYBOARD_MENU) == 0) return InputCode::KEYBOARD_MENU;
	if (strcmp(value, inputDetails::MOUSE_BUTTON_1) == 0) return InputCode::MOUSE_BUTTON_1;
	if (strcmp(value, inputDetails::MOUSE_BUTTON_2) == 0) return InputCode::MOUSE_BUTTON_2;
	if (strcmp(value, inputDetails::MOUSE_BUTTON_3) == 0) return InputCode::MOUSE_BUTTON_3;
	if (strcmp(value, inputDetails::MOUSE_BUTTON_4) == 0) return InputCode::MOUSE_BUTTON_4;
	if (strcmp(value, inputDetails::MOUSE_BUTTON_5) == 0) return InputCode::MOUSE_BUTTON_5;
	if (strcmp(value, inputDetails::MOUSE_BUTTON_6) == 0) return InputCode::MOUSE_BUTTON_6;
	if (strcmp(value, inputDetails::MOUSE_BUTTON_7) == 0) return InputCode::MOUSE_BUTTON_7;
	if (strcmp(value, inputDetails::MOUSE_BUTTON_8) == 0) return InputCode::MOUSE_BUTTON_8;
	if (strcmp(value, inputDetails::MOUSE_LEFT) == 0) return InputCode::MOUSE_LEFT;
	if (strcmp(value, inputDetails::MOUSE_RIGHT) == 0) return InputCode::MOUSE_RIGHT;
	if (strcmp(value, inputDetails::MOUSE_MIDDLE) == 0) return InputCode::MOUSE_MIDDLE;
	if (strcmp(value, inputDetails::XBOX_CONTROLLER_A) == 0) return InputCode::XBOX_CONTROLLER_A;
	if (strcmp(value, inputDetails::XBOX_CONTROLLER_B) == 0) return InputCode::XBOX_CONTROLLER_B;
	if (strcmp(value, inputDetails::XBOX_CONTROLLER_X) == 0) return InputCode::XBOX_CONTROLLER_X;
	if (strcmp(value, inputDetails::XBOX_CONTROLLER_Y) == 0) return InputCode::XBOX_CONTROLLER_Y;
	if (strcmp(value, inputDetails::XBOX_CONTROLLER_START) == 0) return InputCode::XBOX_CONTROLLER_START;
	if (strcmp(value, inputDetails::XBOX_CONTROLLER_SELECT) == 0) return InputCode::XBOX_CONTROLLER_SELECT;
	if (strcmp(value, inputDetails::XBOX_CONTROLLER_MENU) == 0) return InputCode::XBOX_CONTROLLER_MENU;
    if (strcmp(value, inputDetails::XBOX_CONTROLLER_RS) == 0) return InputCode::XBOX_CONTROLLER_RS;
    if (strcmp(value, inputDetails::XBOX_CONTROLLER_LS) == 0) return InputCode::XBOX_CONTROLLER_LS;
    if (strcmp(value, inputDetails::XBOX_CONTROLLER_RB) == 0) return InputCode::XBOX_CONTROLLER_RB;
    if (strcmp(value, inputDetails::XBOX_CONTROLLER_LB) == 0) return InputCode::XBOX_CONTROLLER_LB;
	if (strcmp(value, inputDetails::XBOX_CONTROLLER_UP) == 0) return InputCode::XBOX_CONTROLLER_UP;
	if (strcmp(value, inputDetails::XBOX_CONTROLLER_DOWN) == 0) return InputCode::XBOX_CONTROLLER_DOWN;
	if (strcmp(value, inputDetails::XBOX_CONTROLLER_LEFT) == 0) return InputCode::XBOX_CONTROLLER_LEFT;
	if (strcmp(value, inputDetails::XBOX_CONTROLLER_RIGHT) == 0) return InputCode::XBOX_CONTROLLER_RIGHT;
	if (strcmp(value, inputDetails::XBOX_CONTROLLER_AXIS_LEFT_X) == 0) return InputCode::XBOX_CONTROLLER_AXIS_LEFT_X;
	if (strcmp(value, inputDetails::XBOX_CONTROLLER_AXIS_LEFT_Y) == 0) return InputCode::XBOX_CONTROLLER_AXIS_LEFT_Y;
	if (strcmp(value, inputDetails::XBOX_CONTROLLER_AXIS_RIGHT_X) == 0) return InputCode::XBOX_CONTROLLER_AXIS_RIGHT_X;
	if (strcmp(value, inputDetails::XBOX_CONTROLLER_AXIS_RIGHT_Y) == 0) return InputCode::XBOX_CONTROLLER_AXIS_RIGHT_Y;
	if (strcmp(value, inputDetails::XBOX_CONTROLLER_AXIS_RT) == 0) return InputCode::XBOX_CONTROLLER_AXIS_RT;
	if (strcmp(value, inputDetails::XBOX_CONTROLLER_AXIS_LT) == 0) return InputCode::XBOX_CONTROLLER_AXIS_LT;
	if (strcmp(value, inputDetails::UNSUPPORTED) == 0) return InputCode::UNSUPPORTED;
	return InputCode::UNSUPPORTED;
}

bool isKeyboardCode(const InputCode code) {
	return ((U32) code & 0x01000000) != 0;
}

bool isMouseCode(const InputCode code) {
	return ((U32) code & 0x02000000) != 0;
}

bool isDeviceCode(const InputCode code) {
	return ((U32) code & 0x03000000) != 0;
}

}

bool operator==(Chord const &v1, Chord const &v2) {
	if (v1.size == v2.size) {
		if (v1.size == InputChordSize::_2) {
			return (v1._1.equals(v2._1)) && (v1._2.equals(v2._2));
		} else if (v1.size == InputChordSize::_3) {
			return (v1._1.equals(v2._1)) && (v1._2.equals(v2._2)) && (v1._3.equals(v2._3));
		}
	}
	return false;
}

bool operator!=(Chord const &v1, Chord const &v2) {
	if (v1.size == v2.size) {
		if (v1.size == InputChordSize::_2) {
			return (!v1._1.equals(v2._1)) || (!v1._2.equals(v2._2));
		} else if (v1.size == InputChordSize::_3) {
			return (!v1._1.equals(v2._1)) || (!v1._2.equals(v2._2)) || (!v1._3.equals(v2._3));
		}
	}
	return true;
}


Joystick::~Joystick() {
	if (mInitialized) {
		std::free(mPreviousAxeStates);
		std::free(mPreviousButtonStates);
	}
}


void Joystick::initialize(int index) {
	/*if (glfwJoystickPresent(index)) {
		mIndex = index;
		mConnected = true;
		mInitialized = true;
		mAxeStates = glfwGetJoystickAxes(index, &mAxesCount);
		mButtonStates = glfwGetJoystickButtons(index, &mButtonsCount);

		mPreviousAxeStates = (float *) std::malloc(mAxesCount * sizeof(float));
		mPreviousButtonStates = (unsigned char *) std::malloc(mButtonsCount * sizeof(unsigned char));

		for(int i = 0 ; i < mAxesCount ; i++) {
			mPreviousButtonStates[i] = 0.0f;
		}
		for(int i = 0 ; i < mButtonsCount ; i++) {
			mPreviousButtonStates[i] = 0;
		}
	} else {
		mConnected = false;
		mInitialized = false;
		mIndex = 0;
		mAxesCount = 0;
		mButtonsCount = 0;
		mAxeStates = nullptr;
		mPreviousAxeStates = nullptr;
		mButtonStates = nullptr;
		mPreviousButtonStates = nullptr;
	}*/
}

void Joystick::release() {
	if (mConnected && mInitialized) {
		mConnected = false;
		mInitialized = false;
		mAxeStates = nullptr;
		mButtonStates = nullptr;
		mAxesCount = 0;
		mButtonsCount = 0;

		std::free(mPreviousAxeStates);
		std::free(mPreviousButtonStates);
	}
}

void Joystick::update() {
	/*if (mConnected && mInitialized) {
		// update joystick state
		mAxeStates = glfwGetJoystickAxes(mIndex, &mAxesCount);
		mButtonStates = glfwGetJoystickButtons(mIndex, &mButtonsCount);

		// Read buttons states to submit input to manager if needed
		RawInput rawInput;
		for (int i = 0; i < mButtonsCount; i++) {
			rawInput = RawInput();
			rawInput.idx = this->mIndex;
			rawInput.source = InputSource::DEVICE;
			rawInput.code = InputCode::UNSUPPORTED;

			if (mButtonStates[i] == GLFW_PRESS) {
				rawInput.type = InputType::BUTTON_PRESS;
			}

			if (mPreviousButtonStates[i] == GLFW_RELEASE && mButtonStates[i] == GLFW_PRESS) {
				rawInput.type = InputType::BUTTON_PRESS;
				rawInput.code = mapButtonIdxToInputCode(i);
			}
			else if (mPreviousButtonStates[i] == GLFW_PRESS && mButtonStates[i] == GLFW_PRESS) {
				rawInput.type = InputType::BUTTON_DOWN;
				rawInput.code = mapButtonIdxToInputCode(i);
			}
			else if (mPreviousButtonStates[i] == GLFW_PRESS && mButtonStates[i] == GLFW_RELEASE) {
				rawInput.type = InputType::BUTTON_RELEASE;
				rawInput.code = mapButtonIdxToInputCode(i);
			}

			if (rawInput.code != InputCode::UNSUPPORTED) {
				gInput().registerInput(rawInput);
			}
		}

		// Read axes states to submit input to manager if needed
		for (int i = 0; i < mAxesCount; i++) {
			rawInput = RawInput();
			rawInput.idx = this->mIndex;
			rawInput.source = InputSource::DEVICE;
			rawInput.type = InputType::AXIS;
			rawInput.code = InputCode::UNSUPPORTED;
			rawInput.code = mapAxesIdxToInputCode(i);


			if( rawInput.code == InputCode::XBOX_CONTROLLER_AXIS_RT ||
				rawInput.code == InputCode::XBOX_CONTROLLER_AXIS_LT ) {

				if(mAxeStates[i] > -1.0f && mAxeStates[i] <= 1.0f) {
					gInput().registerInput(rawInput);
				}
			} else if ( (rawInput.code != InputCode::UNSUPPORTED) &&
						(mAxeStates[i] < -0.1f || mAxeStates[i] > 0.1f) ) {
				gInput().registerInput(rawInput);
			}
		}

		std::memcpy(mPreviousAxeStates, mAxeStates, mAxesCount * sizeof(float));
		std::memcpy(mPreviousButtonStates, mButtonStates, mButtonsCount * sizeof(unsigned char));
	}*/
}

InputCode Joystick::mapButtonIdxToInputCode(int idx) {
	switch (idx) {
		case 0:
			return InputCode::XBOX_CONTROLLER_A;
		case 1:
			return InputCode::XBOX_CONTROLLER_B;
		case 2:
			return InputCode::XBOX_CONTROLLER_X;
		case 3:
			return InputCode::XBOX_CONTROLLER_Y;
		case 4:
			return InputCode::XBOX_CONTROLLER_LB;
		case 5:
			return InputCode::XBOX_CONTROLLER_RB;
		case 6:
			return InputCode::XBOX_CONTROLLER_SELECT;
		case 7:
			return InputCode::XBOX_CONTROLLER_START;
		case 8:
			return InputCode::XBOX_CONTROLLER_LS;
		case 9:
			return InputCode::XBOX_CONTROLLER_RS;
		case 10:
			return InputCode::XBOX_CONTROLLER_UP;
		case 11:
			return InputCode::XBOX_CONTROLLER_RIGHT;
		case 12:
			return InputCode::XBOX_CONTROLLER_DOWN;
		case 13:
			return InputCode::XBOX_CONTROLLER_LEFT;
		default:
			return InputCode::UNSUPPORTED;
	};
}

InputCode Joystick::mapAxesIdxToInputCode(int idx) {
	switch (idx) {
		case 0:
			return InputCode::XBOX_CONTROLLER_AXIS_LEFT_X;
		case 1:
			return InputCode::XBOX_CONTROLLER_AXIS_LEFT_Y;
		case 2:
			return InputCode::XBOX_CONTROLLER_AXIS_RIGHT_X;
		case 3:
			return InputCode::XBOX_CONTROLLER_AXIS_RIGHT_Y;
		case 4:
			return InputCode::XBOX_CONTROLLER_AXIS_RT;
		case 5:
			return InputCode::XBOX_CONTROLLER_AXIS_LT;
		default:
			return InputCode::UNSUPPORTED;
	};
}


InputCode sysInputKeyboardCode2GHCode(int sysInputCode) {
	/*if (sysInputCode == GLFW_KEY_SPACE) { return InputCode::KEYBOARD_SPACE; }
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
	if (sysInputCode == GLFW_KEY_MENU) { return InputCode::KEYBOARD_MENU; }*/
	return InputCode::NONE;
}

InputCode sysInputMouseCode2GHCode(int sysInputCode) {
	/*if (sysInputCode == GLFW_MOUSE_BUTTON_1) { return InputCode::MOUSE_BUTTON_1; }
	if (sysInputCode == GLFW_MOUSE_BUTTON_2) { return InputCode::MOUSE_BUTTON_2; }
	if (sysInputCode == GLFW_MOUSE_BUTTON_3) { return InputCode::MOUSE_BUTTON_3; }
	if (sysInputCode == GLFW_MOUSE_BUTTON_4) { return InputCode::MOUSE_BUTTON_4; }
	if (sysInputCode == GLFW_MOUSE_BUTTON_5) { return InputCode::MOUSE_BUTTON_5; }
	if (sysInputCode == GLFW_MOUSE_BUTTON_6) { return InputCode::MOUSE_BUTTON_6; }
	if (sysInputCode == GLFW_MOUSE_BUTTON_7) { return InputCode::MOUSE_BUTTON_7; }
	if (sysInputCode == GLFW_MOUSE_BUTTON_8) { return InputCode::MOUSE_BUTTON_8; }*/
	return InputCode::NONE;
}

}