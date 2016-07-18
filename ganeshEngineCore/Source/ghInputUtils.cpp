#include "ghInputUtils.h"

namespace ganeshEngine {

int InputMatch::m_lastId = 0;

const char* RawInput::sourceMouse = "MOUSE";
const char* RawInput::sourceKeyboard = "KEYBOARD";
const char* RawInput::sourceJoystick = "JOYSTICK";

const char* RawInput::typePress = "PRESS";
const char* RawInput::typeRelease = "RELEASE";
const char* RawInput::typeHold = "HOLD";
const char* RawInput::typeRange= "RANGE";
const char* RawInput::typeMove = "MOVE";

const char* RawInput::keyMouseLeft = "MOUSE_LEFT";
const char* RawInput::keyMouseRight = "MOUSE_RIGHT";
const char* RawInput::keyApostrophe = "APOSTROPHE";
const char* RawInput::keyComma = "COMMA";
const char* RawInput::keyMinus = "MINUS"; // and cortex
const char* RawInput::keyPeriod = "PERIOD";
const char* RawInput::keySlash = "SLASH"; // Paradise city FTW
const char* RawInput::keyNum0 = "NUM_0";
const char* RawInput::keyNum1 = "NUM_1";
const char* RawInput::keyNum2 = "NUM_2";
const char* RawInput::keyNum3 = "NUM_3";
const char* RawInput::keyNum4 = "NUM_4";
const char* RawInput::keyNum5 = "NUM_5";
const char* RawInput::keyNum6 = "NUM_6";
const char* RawInput::keyNum7 = "NUM_7";
const char* RawInput::keyNum8 = "NUM_8";
const char* RawInput::keyNum9 = "NUM_9";
const char* RawInput::keySemicolon = "SEMICOLON";
const char* RawInput::keyEqual = "EQUAL";
const char* RawInput::keyA = "A";
const char* RawInput::keyB = "B";
const char* RawInput::keyC = "C";
const char* RawInput::keyD = "D";
const char* RawInput::keyE = "E";
const char* RawInput::keyF = "F";
const char* RawInput::keyG = "G";
const char* RawInput::keyH = "H";
const char* RawInput::keyI = "I";
const char* RawInput::keyJ = "J";
const char* RawInput::keyK = "K";
const char* RawInput::keyL = "L";
const char* RawInput::keyM = "M";
const char* RawInput::keyN = "N";
const char* RawInput::keyO = "O";
const char* RawInput::keyP = "P";
const char* RawInput::keyQ = "Q";
const char* RawInput::keyR = "R";
const char* RawInput::keyS = "S";
const char* RawInput::keyT = "T";
const char* RawInput::keyU = "U";
const char* RawInput::keyV = "V";
const char* RawInput::keyW = "W";
const char* RawInput::keyX = "X";
const char* RawInput::keyY = "Y";
const char* RawInput::keyZ = "Z";
const char* RawInput::keyLeftBracket = "LEFT_BRACKET";
const char* RawInput::keyBackslash = "BACKSLASH";
const char* RawInput::keyRightBracket = "RIGHT_BRACKET";
const char* RawInput::keyGraveAccent = "GRAVE_ACCENT";
const char* RawInput::keyWorld1 = "WORLD_1";
const char* RawInput::keyWorld2 = "WORLD_2";
const char* RawInput::keyEscape = "ESCAPE"; // the great one
const char* RawInput::keyEnter = "ENTER"; // the matrix
const char* RawInput::keyTab = "TAB";
const char* RawInput::keyBackspace = "BACKSPACE";
const char* RawInput::keyInsert = "INSERT"; //coin
const char* RawInput::keyDelete = "DELETE";
const char* RawInput::keyRight = "RIGHT";
const char* RawInput::keyLeft = "LEFT";
const char* RawInput::keyDown = "DOWN";
const char* RawInput::keyUp = "UP";
const char* RawInput::keyPageUp = "PAGE_UP";
const char* RawInput::keyPageDown = "PAGE_DOWN";
const char* RawInput::keyHome = "HOME"; // sweet home
const char* RawInput::keyEnd = "END"; // never war
const char* RawInput::keyCapsLock = "CAPS_LOCK";
const char* RawInput::keyScrollLock = "SCROLL_LOCK";
const char* RawInput::keyNumLock = "NUM_LOCK";
const char* RawInput::keyPrintScreen = "PRINT_SCREEN";
const char* RawInput::keyPause = "PAUSE";
const char* RawInput::keyF1 = "F1";
const char* RawInput::keyF2 = "F2";
const char* RawInput::keyF3 = "F3";
const char* RawInput::keyF4 = "F4";
const char* RawInput::keyF5 = "F5";
const char* RawInput::keyF6 = "F6";
const char* RawInput::keyF7 = "F7";
const char* RawInput::keyF8 = "F8";
const char* RawInput::keyF9 = "F9";
const char* RawInput::keyF10 = "F10";
const char* RawInput::keyF11 = "F11";
const char* RawInput::keyF12 = "F12";
const char* RawInput::keyF13 = "F13";
const char* RawInput::keyF14 = "F14";
const char* RawInput::keyF15 = "F15";
const char* RawInput::keyF16 = "F16";
const char* RawInput::keyF17 = "F17";
const char* RawInput::keyF18 = "F18";
const char* RawInput::keyF19 = "F19";
const char* RawInput::keyF20 = "F20";
const char* RawInput::keyF21 = "F21";
const char* RawInput::keyF22 = "F22";
const char* RawInput::keyF23 = "F23";
const char* RawInput::keyF24 = "F24";
const char* RawInput::keyF25 = "F25";
const char* RawInput::keyKp0 = "KP_0";
const char* RawInput::keyKp1 = "KP_1";
const char* RawInput::keyKp2 = "KP_2";
const char* RawInput::keyKp3 = "KP_3";
const char* RawInput::keyKp4 = "KP_4";
const char* RawInput::keyKp5 = "KP_5";
const char* RawInput::keyKp6 = "KP_6";
const char* RawInput::keyKp7 = "KP_7";
const char* RawInput::keyKp8 = "KP_8";
const char* RawInput::keyKp9 = "KP_9";
const char* RawInput::keyKpDecimal = "KP_DECIMAL";
const char* RawInput::keyKpDivide = "KP_DIVIDE";
const char* RawInput::keyKpMultiply = "KP_MULTIPLY";
const char* RawInput::keyKpSubtract = "KP_SUBTRACT";
const char* RawInput::keyKpAdd = "KP_ADD";
const char* RawInput::keyKpEnter = "KP_ENTER";
const char* RawInput::keyKpEqual = "KP_EQUAL";
const char* RawInput::keyLeftShift = "LEFT_SHIFT";
const char* RawInput::keyLeftControl = "LEFT_CONTROL";
const char* RawInput::keyLeftAlt = "LEFT_ALT";
const char* RawInput::keyLeftSuper = "LEFT_SUPER";
const char* RawInput::keyRightShift = "RIGHT_SHIFT";
const char* RawInput::keyRightControl = "RIGHT_CONTROL";
const char* RawInput::keyRightAlt = "RIGHT_ALT";
const char* RawInput::keyRightSuper = "RIGHT_SUPER";
const char* RawInput::keyMenu = "MENU";

template<>
RawInput::SOURCE RawInput::fromString<RawInput::SOURCE>(const char* value) {
    if(strcmp(value, sourceMouse)==0) return RawInput::SOURCE::MOUSE;
    if(strcmp(value, sourceKeyboard)==0) return RawInput::SOURCE::KEYBOARD;
    if(strcmp(value, sourceJoystick)==0) return RawInput::SOURCE::JOYSTICK;
    assert(false);
}

template<>
RawInput::TYPE RawInput::fromString<RawInput::TYPE>(const char* value) {
    if(strcmp(value, typePress)==0) return RawInput::TYPE::PRESS;
    if(strcmp(value, typeRelease)==0) return RawInput::TYPE::RELEASE;
    if(strcmp(value, typeHold)==0) return RawInput::TYPE::HOLD;
    if(strcmp(value, typeRange)==0) return RawInput::TYPE::RANGE;
    if(strcmp(value, typeMove)==0) return RawInput::TYPE::MOVE;
    assert(false);
}

template<>
RawInput::KEY RawInput::fromString<RawInput::KEY>(const char* value) {
    if(strcmp(value, keyMouseLeft)==0) return RawInput::KEY::MOUSE_LEFT;
    if(strcmp(value, keyMouseRight)==0) return RawInput::KEY::MOUSE_RIGHT;
    if(strcmp(value, keyApostrophe)==0) return RawInput::KEY::APOSTROPHE;
    if(strcmp(value, keyComma)==0) return RawInput::KEY::COMMA;
    if(strcmp(value, keyMinus)==0) return RawInput::KEY::MINUS;
    if(strcmp(value, keyPeriod)==0) return RawInput::KEY::PERIOD;
    if(strcmp(value, keySlash)==0) return RawInput::KEY::SLASH;
    if(strcmp(value, keyNum0)==0) return RawInput::KEY::NUM_0;
    if(strcmp(value, keyNum1)==0) return RawInput::KEY::NUM_1;
    if(strcmp(value, keyNum2)==0) return RawInput::KEY::NUM_2;
    if(strcmp(value, keyNum3)==0) return RawInput::KEY::NUM_3;
    if(strcmp(value, keyNum4)==0) return RawInput::KEY::NUM_4;
    if(strcmp(value, keyNum5)==0) return RawInput::KEY::NUM_5;
    if(strcmp(value, keyNum6)==0) return RawInput::KEY::NUM_6;
    if(strcmp(value, keyNum7)==0) return RawInput::KEY::NUM_7;
    if(strcmp(value, keyNum8)==0) return RawInput::KEY::NUM_8;
    if(strcmp(value, keyNum9)==0) return RawInput::KEY::NUM_9;
    if(strcmp(value, keySemicolon)==0) return RawInput::KEY::SEMICOLON;
    if(strcmp(value, keyEqual)==0) return RawInput::KEY::EQUAL;
    if(strcmp(value, keyA)==0) return RawInput::KEY::A;
    if(strcmp(value, keyB)==0) return RawInput::KEY::B;
    if(strcmp(value, keyC)==0) return RawInput::KEY::C;
    if(strcmp(value, keyD)==0) return RawInput::KEY::D;
    if(strcmp(value, keyE)==0) return RawInput::KEY::E;
    if(strcmp(value, keyF)==0) return RawInput::KEY::F;
    if(strcmp(value, keyG)==0) return RawInput::KEY::G;
    if(strcmp(value, keyH)==0) return RawInput::KEY::H;
    if(strcmp(value, keyI)==0) return RawInput::KEY::I;
    if(strcmp(value, keyJ)==0) return RawInput::KEY::J;
    if(strcmp(value, keyK)==0) return RawInput::KEY::K;
    if(strcmp(value, keyL)==0) return RawInput::KEY::L;
    if(strcmp(value, keyM)==0) return RawInput::KEY::M;
    if(strcmp(value, keyN)==0) return RawInput::KEY::N;
    if(strcmp(value, keyO)==0) return RawInput::KEY::O;
    if(strcmp(value, keyP)==0) return RawInput::KEY::P;
    if(strcmp(value, keyQ)==0) return RawInput::KEY::Q;
    if(strcmp(value, keyR)==0) return RawInput::KEY::R;
    if(strcmp(value, keyS)==0) return RawInput::KEY::S;
    if(strcmp(value, keyT)==0) return RawInput::KEY::T;
    if(strcmp(value, keyU)==0) return RawInput::KEY::U;
    if(strcmp(value, keyV)==0) return RawInput::KEY::V;
    if(strcmp(value, keyW)==0) return RawInput::KEY::W;
    if(strcmp(value, keyX)==0) return RawInput::KEY::X;
    if(strcmp(value, keyY)==0) return RawInput::KEY::Y;
    if(strcmp(value, keyZ)==0) return RawInput::KEY::Z;
    if(strcmp(value, keyLeftBracket)==0) return RawInput::KEY::LEFT_BRACKET;
    if(strcmp(value, keyBackslash)==0) return RawInput::KEY::BACKSLASH;
    if(strcmp(value, keyRightBracket)==0) return RawInput::KEY::RIGHT_BRACKET;
    if(strcmp(value, keyGraveAccent)==0) return RawInput::KEY::GRAVE_ACCENT;
    if(strcmp(value, keyWorld1)==0) return RawInput::KEY::WORLD_1;
    if(strcmp(value, keyWorld2)==0) return RawInput::KEY::WORLD_2;
    if(strcmp(value, keyEscape)==0) return RawInput::KEY::ESCAPE;
    if(strcmp(value, keyEnter)==0) return RawInput::KEY::ENTER;
    if(strcmp(value, keyTab)==0) return RawInput::KEY::TAB;
    if(strcmp(value, keyBackspace)==0) return RawInput::KEY::BACKSPACE;
    if(strcmp(value, keyInsert)==0) return RawInput::KEY::INSERT;
    if(strcmp(value, keyDelete)==0) return RawInput::KEY::DELETE;
    if(strcmp(value, keyRight)==0) return RawInput::KEY::RIGHT;
    if(strcmp(value, keyLeft)==0) return RawInput::KEY::LEFT;
    if(strcmp(value, keyDown)==0) return RawInput::KEY::DOWN;
    if(strcmp(value, keyUp)==0) return RawInput::KEY::UP;
    if(strcmp(value, keyPageUp)==0) return RawInput::KEY::PAGE_UP;
    if(strcmp(value, keyPageDown)==0) return RawInput::KEY::PAGE_DOWN;
    if(strcmp(value, keyHome)==0) return RawInput::KEY::HOME;
    if(strcmp(value, keyEnd)==0) return RawInput::KEY::END;
    if(strcmp(value, keyCapsLock)==0) return RawInput::KEY::CAPS_LOCK;
    if(strcmp(value, keyScrollLock)==0) return RawInput::KEY::SCROLL_LOCK;
    if(strcmp(value, keyNumLock)==0) return RawInput::KEY::NUM_LOCK;
    if(strcmp(value, keyPrintScreen)==0) return RawInput::KEY::PRINT_SCREEN;
    if(strcmp(value, keyPause)==0) return RawInput::KEY::PAUSE;
    if(strcmp(value, keyF1)==0) return RawInput::KEY::F1;
    if(strcmp(value, keyF2)==0) return RawInput::KEY::F2;
    if(strcmp(value, keyF3)==0) return RawInput::KEY::F3;
    if(strcmp(value, keyF4)==0) return RawInput::KEY::F4;
    if(strcmp(value, keyF5)==0) return RawInput::KEY::F5;
    if(strcmp(value, keyF6)==0) return RawInput::KEY::F6;
    if(strcmp(value, keyF7)==0) return RawInput::KEY::F7;
    if(strcmp(value, keyF8)==0) return RawInput::KEY::F8;
    if(strcmp(value, keyF9)==0) return RawInput::KEY::F9;
    if(strcmp(value, keyF10)==0) return RawInput::KEY::F10;
    if(strcmp(value, keyF11)==0) return RawInput::KEY::F11;
    if(strcmp(value, keyF12)==0) return RawInput::KEY::F12;
    if(strcmp(value, keyF13)==0) return RawInput::KEY::F13;
    if(strcmp(value, keyF14)==0) return RawInput::KEY::F14;
    if(strcmp(value, keyF15)==0) return RawInput::KEY::F15;
    if(strcmp(value, keyF16)==0) return RawInput::KEY::F16;
    if(strcmp(value, keyF17)==0) return RawInput::KEY::F17;
    if(strcmp(value, keyF18)==0) return RawInput::KEY::F18;
    if(strcmp(value, keyF19)==0) return RawInput::KEY::F19;
    if(strcmp(value, keyF20)==0) return RawInput::KEY::F20;
    if(strcmp(value, keyF21)==0) return RawInput::KEY::F21;
    if(strcmp(value, keyF22)==0) return RawInput::KEY::F22;
    if(strcmp(value, keyF23)==0) return RawInput::KEY::F23;
    if(strcmp(value, keyF24)==0) return RawInput::KEY::F24;
    if(strcmp(value, keyF25)==0) return RawInput::KEY::F25;
    if(strcmp(value, keyKp0)==0) return RawInput::KEY::KP_0;
    if(strcmp(value, keyKp1)==0) return RawInput::KEY::KP_1;
    if(strcmp(value, keyKp2)==0) return RawInput::KEY::KP_2;
    if(strcmp(value, keyKp3)==0) return RawInput::KEY::KP_3;
    if(strcmp(value, keyKp4)==0) return RawInput::KEY::KP_4;
    if(strcmp(value, keyKp5)==0) return RawInput::KEY::KP_5;
    if(strcmp(value, keyKp6)==0) return RawInput::KEY::KP_6;
    if(strcmp(value, keyKp7)==0) return RawInput::KEY::KP_7;
    if(strcmp(value, keyKp8)==0) return RawInput::KEY::KP_8;
    if(strcmp(value, keyKp9)==0) return RawInput::KEY::KP_9;
    if(strcmp(value, keyKpDecimal)==0) return RawInput::KEY::KP_DECIMAL;
    if(strcmp(value, keyKpDivide)==0) return RawInput::KEY::KP_DIVIDE;
    if(strcmp(value, keyKpMultiply)==0) return RawInput::KEY::KP_MULTIPLY;
    if(strcmp(value, keyKpSubtract)==0) return RawInput::KEY::KP_SUBTRACT;
    if(strcmp(value, keyKpAdd)==0) return RawInput::KEY::KP_ADD;
    if(strcmp(value, keyKpEnter)==0) return RawInput::KEY::KP_ENTER;
    if(strcmp(value, keyKpEqual)==0) return RawInput::KEY::KP_EQUAL;
    if(strcmp(value, keyLeftShift)==0) return RawInput::KEY::LEFT_SHIFT;
    if(strcmp(value, keyLeftControl)==0) return RawInput::KEY::LEFT_CONTROL;
    if(strcmp(value, keyLeftAlt)==0) return RawInput::KEY::LEFT_ALT;
    if(strcmp(value, keyLeftSuper)==0) return RawInput::KEY::LEFT_SUPER;
    if(strcmp(value, keyRightShift)==0) return RawInput::KEY::RIGHT_SHIFT;
    if(strcmp(value, keyRightControl)==0) return RawInput::KEY::RIGHT_CONTROL;
    if(strcmp(value, keyRightAlt)==0) return RawInput::KEY::RIGHT_ALT;
    if(strcmp(value, keyRightSuper)==0) return RawInput::KEY::RIGHT_SUPER;
    if(strcmp(value, keyMenu)==0) return RawInput::KEY::MENU;
    assert(false);
}


InputMatch::InputMatch() {
    m_id = m_lastId++;
}

int InputMatch::getId() {
    return m_id;
}

}