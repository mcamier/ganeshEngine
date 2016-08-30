#ifndef GANESHENGINE_GHINPUTUTILS_H
#define GANESHENGINE_GHINPUTUTILS_H

#include "ghHeaders.h"
#include <vector>
#include <cstring>
#include <functional>
#include <GLFW/glfw3.h>

#define GH_KEYBOARD_KEY_COUNT       120
#define GH_MOUSE_KEY_COUNT          8
#define GH_MAX_JOYSTICK             GLFW_JOYSTICK_LAST

#define GH_STATE_RELEASED           1
#define GH_STATE_PRESSED            2
#define GH_STATE_HELD               3

constexpr int ghKeyboardKeys[GH_KEYBOARD_KEY_COUNT] = {
        //GLFW_KEY_UNKNOWN,
        GLFW_KEY_SPACE,
        GLFW_KEY_APOSTROPHE,
        GLFW_KEY_COMMA,
        GLFW_KEY_MINUS,
        GLFW_KEY_PERIOD,
        GLFW_KEY_SLASH,
        GLFW_KEY_0,
        GLFW_KEY_1,
        GLFW_KEY_2,
        GLFW_KEY_3,
        GLFW_KEY_4,
        GLFW_KEY_5,
        GLFW_KEY_6,
        GLFW_KEY_7,
        GLFW_KEY_8,
        GLFW_KEY_9,
        GLFW_KEY_SEMICOLON,
        GLFW_KEY_EQUAL,
        GLFW_KEY_A,
        GLFW_KEY_B,
        GLFW_KEY_C,
        GLFW_KEY_D,
        GLFW_KEY_E,
        GLFW_KEY_F,
        GLFW_KEY_G,
        GLFW_KEY_H,
        GLFW_KEY_I,
        GLFW_KEY_J,
        GLFW_KEY_K,
        GLFW_KEY_L,
        GLFW_KEY_M,
        GLFW_KEY_N,
        GLFW_KEY_O,
        GLFW_KEY_P,
        GLFW_KEY_Q,
        GLFW_KEY_R,
        GLFW_KEY_S,
        GLFW_KEY_T,
        GLFW_KEY_U,
        GLFW_KEY_V,
        GLFW_KEY_W,
        GLFW_KEY_X,
        GLFW_KEY_Y,
        GLFW_KEY_Z,
        GLFW_KEY_LEFT_BRACKET,
        GLFW_KEY_BACKSLASH,
        GLFW_KEY_RIGHT_BRACKET,
        GLFW_KEY_GRAVE_ACCENT,
        GLFW_KEY_WORLD_1,
        GLFW_KEY_WORLD_2,
        GLFW_KEY_ESCAPE,
        GLFW_KEY_ENTER,
        GLFW_KEY_TAB,
        GLFW_KEY_BACKSPACE,
        GLFW_KEY_INSERT,
        GLFW_KEY_DELETE,
        GLFW_KEY_RIGHT,
        GLFW_KEY_LEFT,
        GLFW_KEY_DOWN,
        GLFW_KEY_UP,
        GLFW_KEY_PAGE_UP,
        GLFW_KEY_PAGE_DOWN,
        GLFW_KEY_HOME,
        GLFW_KEY_END,
        GLFW_KEY_CAPS_LOCK,
        GLFW_KEY_SCROLL_LOCK,
        GLFW_KEY_NUM_LOCK,
        GLFW_KEY_PRINT_SCREEN,
        GLFW_KEY_PAUSE,
        GLFW_KEY_F1,
        GLFW_KEY_F2,
        GLFW_KEY_F3,
        GLFW_KEY_F4,
        GLFW_KEY_F5,
        GLFW_KEY_F6,
        GLFW_KEY_F7,
        GLFW_KEY_F8,
        GLFW_KEY_F9,
        GLFW_KEY_F10,
        GLFW_KEY_F11,
        GLFW_KEY_F12,
        GLFW_KEY_F13,
        GLFW_KEY_F14,
        GLFW_KEY_F15,
        GLFW_KEY_F16,
        GLFW_KEY_F17,
        GLFW_KEY_F18,
        GLFW_KEY_F19,
        GLFW_KEY_F20,
        GLFW_KEY_F21,
        GLFW_KEY_F22,
        GLFW_KEY_F23,
        GLFW_KEY_F24,
        GLFW_KEY_F25,
        GLFW_KEY_KP_0,
        GLFW_KEY_KP_1,
        GLFW_KEY_KP_2,
        GLFW_KEY_KP_3,
        GLFW_KEY_KP_4,
        GLFW_KEY_KP_5,
        GLFW_KEY_KP_6,
        GLFW_KEY_KP_7,
        GLFW_KEY_KP_8,
        GLFW_KEY_KP_9,
        GLFW_KEY_KP_DECIMAL,
        GLFW_KEY_KP_DIVIDE,
        GLFW_KEY_KP_MULTIPLY,
        GLFW_KEY_KP_SUBTRACT,
        GLFW_KEY_KP_ADD,
        GLFW_KEY_KP_ENTER,
        GLFW_KEY_KP_EQUAL,
        GLFW_KEY_LEFT_SHIFT,
        GLFW_KEY_LEFT_CONTROL,
        GLFW_KEY_LEFT_ALT,
        GLFW_KEY_LEFT_SUPER,
        GLFW_KEY_RIGHT_SHIFT,
        GLFW_KEY_RIGHT_CONTROL,
        GLFW_KEY_RIGHT_ALT,
        GLFW_KEY_RIGHT_SUPER,
        GLFW_KEY_MENU
};

constexpr int ghMouseKeys[GH_MOUSE_KEY_COUNT] = {
    GLFW_MOUSE_BUTTON_1,
    GLFW_MOUSE_BUTTON_2,
    GLFW_MOUSE_BUTTON_3,
    GLFW_MOUSE_BUTTON_4,
    GLFW_MOUSE_BUTTON_5,
    GLFW_MOUSE_BUTTON_6,
    GLFW_MOUSE_BUTTON_7,
    GLFW_MOUSE_BUTTON_8
};

namespace ganeshEngine {

using namespace std;

/**
 *
 */
class Joystick {
private:
	int m_index;
	int axeCount;
	int buttonCount;

	const unsigned char* axes;
	const float* buttons;
	float* previousButtons;

public:
	Joystick(int index) : m_index(index) {
		glfwGetJoystickAxes(index, &buttonCount);
		previousButtons = static_cast<float*>(malloc(buttonCount * sizeof(float)));
	}
	virtual ~Joystick() {
		free(previousButtons);
	}

	void update() {
		//std::memcpy(previousButtons, buttons, sizeof previousButtons);
		axes = glfwGetJoystickButtons(m_index, &axeCount);
		buttons = glfwGetJoystickAxes(m_index, &buttonCount);
	}
};

/**
 * Chord is a combination of two or three pressed at the same time
 * resulting in one action
 */
enum class CHORD_SIZE : int {
	_2 = 2,
	_3 = 3
};

class RawInput {
private:
	const static char *undefined;

	const static char *sourceMouse;
	const static char *sourceKeyboard;
	const static char *sourceJoystick;

	const static char *typePress;
	const static char *typeRelease;
	const static char *typeDown;
	const static char *typeRange;
	const static char *typeMove;

	const static char *keyMouseLeft;
	const static char *keyMouseRight;
	const static char *keyMouseMiddle;
	const static char *keyApostrophe;
	const static char *keyComma;
	const static char *keyMinus;
	const static char *keyPeriod;
	const static char *keySlash;
	const static char *keyNum0;
	const static char *keyNum1;
	const static char *keyNum2;
	const static char *keyNum3;
	const static char *keyNum4;
	const static char *keyNum5;
	const static char *keyNum6;
	const static char *keyNum7;
	const static char *keyNum8;
	const static char *keyNum9;
	const static char *keySemicolon;
	const static char *keyEqual;
	const static char *keySpace;
	const static char *keyA;
	const static char *keyB;
	const static char *keyC;
	const static char *keyD;
	const static char *keyE;
	const static char *keyF;
	const static char *keyG;
	const static char *keyH;
	const static char *keyI;
	const static char *keyJ;
	const static char *keyK;
	const static char *keyL;
	const static char *keyM;
	const static char *keyN;
	const static char *keyO;
	const static char *keyP;
	const static char *keyQ;
	const static char *keyR;
	const static char *keyS;
	const static char *keyT;
	const static char *keyU;
	const static char *keyV;
	const static char *keyW;
	const static char *keyX;
	const static char *keyY;
	const static char *keyZ;
	const static char *keyLeftBracket;
	const static char *keyBackslash;
	const static char *keyRightBracket;
	const static char *keyGraveAccent;
	const static char *keyWorld1;
	const static char *keyWorld2;
	const static char *keyEscape;
	const static char *keyEnter;
	const static char *keyTab;
	const static char *keyBackspace;
	const static char *keyInsert;
	const static char *keyDelete;
	const static char *keyRight;
	const static char *keyLeft;
	const static char *keyDown;
	const static char *keyUp;
	const static char *keyPageUp;
	const static char *keyPageDown;
	const static char *keyHome;
	const static char *keyEnd;
	const static char *keyCapsLock;
	const static char *keyScrollLock;
	const static char *keyNumLock;
	const static char *keyPrintScreen;
	const static char *keyPause;
	const static char *keyF1;
	const static char *keyF2;
	const static char *keyF3;
	const static char *keyF4;
	const static char *keyF5;
	const static char *keyF6;
	const static char *keyF7;
	const static char *keyF8;
	const static char *keyF9;
	const static char *keyF10;
	const static char *keyF11;
	const static char *keyF12;
	const static char *keyF13;
	const static char *keyF14;
	const static char *keyF15;
	const static char *keyF16;
	const static char *keyF17;
	const static char *keyF18;
	const static char *keyF19;
	const static char *keyF20;
	const static char *keyF21;
	const static char *keyF22;
	const static char *keyF23;
	const static char *keyF24;
	const static char *keyF25;
	const static char *keyKp0;
	const static char *keyKp1;
	const static char *keyKp2;
	const static char *keyKp3;
	const static char *keyKp4;
	const static char *keyKp5;
	const static char *keyKp6;
	const static char *keyKp7;
	const static char *keyKp8;
	const static char *keyKp9;
	const static char *keyKpDecimal;
	const static char *keyKpDivide;
	const static char *keyKpMultiply;
	const static char *keyKpSubtract;
	const static char *keyKpAdd;
	const static char *keyKpEnter;
	const static char *keyKpEqual;
	const static char *keyLeftShift;
	const static char *keyLeftControl;
	const static char *keyLeftAlt;
	const static char *keyLeftSuper;
	const static char *keyRightShift;
	const static char *keyRightControl;
	const static char *keyRightAlt;
	const static char *keyRightSuper;
	const static char *keyMenu;

public:

	/**
	 * Supported input devices
	 */
	enum class SOURCE : int {
		MOUSE = 1,
		KEYBOARD = 2,
		JOYSTICK = 3,
		UNDEFINED = 0
	};

	/**
	 * Kind of input
	 *
	 * PRESS: when a button get pressed, only triggered once, even is key is kept down
	 * RELEASE: when a button get released
	 * DOWN: when a button is pressed
	 * RANGE: value between 0 and 1, for instance the xbox controller triggers
	 * MOVE: 3 dimensional floats
	 */
	enum class TYPE : int {
		PRESS = 1,
		DOWN = 2,
		RELEASE = 3,
		RANGE = 4,
		MOVE = 5,
		UNDEFINED = 0
	};

	/**
	 * Every supported key/button which could be pressed, released or held
	 * Note this enum regroup regardless keyboard's key, mouse's button as
	 * well as gamepad's button
	 */
	enum class KEY : int {
        SPACE = ghKeyboardKeys[0],
        APOSTROPHE = ghKeyboardKeys[1],
        COMMA = ghKeyboardKeys[2],
        MINUS = ghKeyboardKeys[3],
        PERIOD = ghKeyboardKeys[4],
        SLASH = ghKeyboardKeys[5],
        NUM_0 = ghKeyboardKeys[6],
        NUM_1 = ghKeyboardKeys[7],
        NUM_2 = ghKeyboardKeys[8],
        NUM_3 = ghKeyboardKeys[9],
        NUM_4 = ghKeyboardKeys[10],
        NUM_5 = ghKeyboardKeys[11],
        NUM_6 = ghKeyboardKeys[12],
        NUM_7 = ghKeyboardKeys[13],
        NUM_8 = ghKeyboardKeys[14],
        NUM_9 = ghKeyboardKeys[15],
        SEMICOLON = ghKeyboardKeys[16],
        EQUAL = ghKeyboardKeys[17],
        A = ghKeyboardKeys[18],
        B = ghKeyboardKeys[19],
        C = ghKeyboardKeys[20],
        D = ghKeyboardKeys[21],
        E = ghKeyboardKeys[22],
        F = ghKeyboardKeys[23],
        G = ghKeyboardKeys[24],
        H = ghKeyboardKeys[25],
        I = ghKeyboardKeys[26],
        J = ghKeyboardKeys[27],
        K = ghKeyboardKeys[28],
        L = ghKeyboardKeys[29],
        M = ghKeyboardKeys[30],
        N = ghKeyboardKeys[31],
        O = ghKeyboardKeys[32],
        P = ghKeyboardKeys[33],
        Q = ghKeyboardKeys[34],
        R = ghKeyboardKeys[35],
        S = ghKeyboardKeys[36],
        T = ghKeyboardKeys[37],
        U = ghKeyboardKeys[38],
        V = ghKeyboardKeys[39],
        W = ghKeyboardKeys[40],
        X = ghKeyboardKeys[41],
        Y = ghKeyboardKeys[42],
        Z = ghKeyboardKeys[43],
        LEFT_BRACKET = ghKeyboardKeys[44],
        BACKSLASH = ghKeyboardKeys[45],
        RIGHT_BRACKET = ghKeyboardKeys[46],
        GRAVE_ACCENT = ghKeyboardKeys[47],
        WORLD_1 = ghKeyboardKeys[48],
        WORLD_2 = ghKeyboardKeys[49],
        ESCAPE = ghKeyboardKeys[50],
        ENTER = ghKeyboardKeys[51],
        TAB = ghKeyboardKeys[52],
        BACKSPACE = ghKeyboardKeys[53],
        INSERT = ghKeyboardKeys[54],
        DELETE = ghKeyboardKeys[55],
        RIGHT = ghKeyboardKeys[56],
        LEFT = ghKeyboardKeys[57],
        DOWN = ghKeyboardKeys[58],
        UP = ghKeyboardKeys[59],
        PAGE_UP = ghKeyboardKeys[60],
        PAGE_DOWN = ghKeyboardKeys[61],
        HOME = ghKeyboardKeys[62],
        END = ghKeyboardKeys[63],
        CAPS_LOCK = ghKeyboardKeys[64],
        SCROLL_LOCK = ghKeyboardKeys[65],
        NUM_LOCK = ghKeyboardKeys[66],
        PRINT_SCREEN = ghKeyboardKeys[67],
        PAUSE = ghKeyboardKeys[68],
        F1 = ghKeyboardKeys[69],
        F2 = ghKeyboardKeys[70],
        F3 = ghKeyboardKeys[71],
        F4 = ghKeyboardKeys[72],
        F5 = ghKeyboardKeys[73],
        F6 = ghKeyboardKeys[74],
        F7 = ghKeyboardKeys[75],
        F8 = ghKeyboardKeys[76],
        F9 = ghKeyboardKeys[77],
        F10 = ghKeyboardKeys[78],
        F11 = ghKeyboardKeys[79],
        F12 = ghKeyboardKeys[80],
        F13 = ghKeyboardKeys[81],
        F14 = ghKeyboardKeys[82],
        F15 = ghKeyboardKeys[83],
        F16 = ghKeyboardKeys[84],
        F17 = ghKeyboardKeys[85],
        F18 = ghKeyboardKeys[86],
        F19 = ghKeyboardKeys[87],
        F20 = ghKeyboardKeys[88],
        F21 = ghKeyboardKeys[89],
        F22 = ghKeyboardKeys[90],
        F23 = ghKeyboardKeys[91],
        F24 = ghKeyboardKeys[92],
        F25 = ghKeyboardKeys[93],
        KP_0 = ghKeyboardKeys[94],
        KP_1 = ghKeyboardKeys[95],
        KP_2 = ghKeyboardKeys[96],
        KP_3 = ghKeyboardKeys[97],
        KP_4 = ghKeyboardKeys[98],
        KP_5 = ghKeyboardKeys[99],
        KP_6 = ghKeyboardKeys[100],
        KP_7 = ghKeyboardKeys[101],
        KP_8 = ghKeyboardKeys[102],
        KP_9 = ghKeyboardKeys[103],
        KP_DECIMAL = ghKeyboardKeys[104],
        KP_DIVIDE = ghKeyboardKeys[105],
        KP_MULTIPLY = ghKeyboardKeys[106],
        KP_SUBTRACT = ghKeyboardKeys[107],
        KP_ADD = ghKeyboardKeys[108],
        KP_ENTER = ghKeyboardKeys[109],
        KP_EQUAL = ghKeyboardKeys[110],
        LEFT_SHIFT = ghKeyboardKeys[111],
        LEFT_CONTROL = ghKeyboardKeys[112],
        LEFT_ALT = ghKeyboardKeys[113],
        LEFT_SUPER = ghKeyboardKeys[114],
        RIGHT_SHIFT = ghKeyboardKeys[115],
        RIGHT_CONTROL = ghKeyboardKeys[116],
        RIGHT_ALT = ghKeyboardKeys[117],
        RIGHT_SUPER = ghKeyboardKeys[118],
        MENU = ghKeyboardKeys[119],

        MOUSE_LEFT = ghMouseKeys[0],
        MOUSE_RIGHT = ghMouseKeys[1],
        MOUSE_MIDDLE = ghMouseKeys[2],

        UNDEFINED = 9999
	};

	/**
	 * Convienent function (especially for debug) providing the enum value of a given
	 * for a key described by its name
	 *
	 * @param value name of the key
	 * @return the enum value
	 */
	template<typename K>
	static K fromString(const char *value);

	/**
	 *
	 * @param value
	 * @return
	 */
	template<typename K>
	static const char *toString(const K value);
};

/** Store informations for all inputs that can be either pressed,
 * released, or held (like keyboard keys, joysticks buttons or
 * mouse buttons)
 */
typedef struct buttonData_s {
	int mods;
	long HoldDurationSecond;
} buttonData;

typedef struct rangeData_s {
	double x;
	double y;
	double z;
} rangeData;

typedef struct moveData_s {
	float x;
	float y;
	float z;
} moveData;

/**
 * Store informations from an input got from the system input layer
 * (GLFW by the time, should be later available through interface)
 */
typedef struct rawInput_s {
	/** From which device the input comes from
	 */
	RawInput::SOURCE source;

	/** Type of the received input
	 */
	RawInput::TYPE type;

	/** Key of the received input, could be set with NONE value
	 * for certain kind of input
	 */
	RawInput::KEY key;

	/** Time when input occured
	 */
	long timestamp;

	/**
	 *
	 */
	float chordDetectionLifetimeS;

	/** Index of the devices that generates the input
	 *
	 * @note will be unrelevant value for the keyboard or the mouse
	 * device source but significant when multiple xbox controllers are
	 * plugged in
	 */
	int idx;

	/** Payload informations
	 */
	union datas_u {
		buttonData button;
		rangeData range;
		moveData move;
	} data;
} rawInput;

/**
 *
 */
class InputMatch {
public:
	RawInput::SOURCE m_source {RawInput::SOURCE::UNDEFINED};
	RawInput::TYPE m_type {RawInput::TYPE::UNDEFINED};
	RawInput::KEY m_key {RawInput::KEY::UNDEFINED};
	U32 m_callbackNameHash {0};

	InputMatch() {}

	InputMatch(RawInput::SOURCE source, RawInput::TYPE type, RawInput::KEY key, U32 callbackHash) :
			m_source(source), m_type(type), m_key(key), m_callbackNameHash(callbackHash) {}
};

/**
 *
 */
class Chord {
public:
	constexpr static const float DETECTION_DURATION_SECOND = 0.02f;

	CHORD_SIZE size;
	InputMatch _1;
	InputMatch _2;
	InputMatch _3;
	U32 m_callbackNameHash;

public:
	Chord(U32 callbackNameHash, InputMatch i1, InputMatch i2) :
			size(CHORD_SIZE::_2),
			_1(i1), _2(i2),
			m_callbackNameHash(callbackNameHash) {}

	Chord(U32 callbackNameHash, InputMatch i1, InputMatch i2, InputMatch i3) :
			size(CHORD_SIZE::_3),
			_1(i1), _2(i2), _3(i3),
			m_callbackNameHash(callbackNameHash) {}

    bool containsRawInput(RawInput::SOURCE source, RawInput::TYPE type ,RawInput::KEY key) const {
        if(size == CHORD_SIZE::_3) {
            return ((_1.m_source == source && _1.m_type == type && _1.m_key == key) ||
                    (_2.m_source == source && _2.m_type == type && _2.m_key == key) ||
                    (_3.m_source == source && _3.m_type == type && _3.m_key == key));
        } else if(size == CHORD_SIZE::_2) {
            return ((_1.m_source == source && _1.m_type == type && _1.m_key == key) ||
                    (_2.m_source == source && _2.m_type == type && _2.m_key == key));
        }
        return false;
    }

    int findFirstInputFrom(vector<rawInput> &listInputs) const {
        for(int i = 0 ; i<listInputs.size() ; ++i) {
            auto const& ri = listInputs[i];
            if(this->_1.m_source == ri.source &&
               this->_1.m_type == ri.type &&
               this->_1.m_key == ri.key) {
                return i;
            }
        }
        return -1;
    }

    int findSecondInputFrom(vector<rawInput> &listInputs) const {
        for(int i = 0 ; i<listInputs.size() ; ++i) {
            auto const& ri = listInputs[i];
            if(this->_2.m_source == ri.source &&
               this->_2.m_type == ri.type &&
               this->_2.m_key == ri.key) {
                return i;
            }
        }
        return -1;
    }

    int findThirdInputFrom(vector<rawInput> &listInputs) const {
        if(size != CHORD_SIZE::_3) return -1;
        for(int i = 0 ; i<listInputs.size() ; ++i) {
            auto const& ri = listInputs[i];
            if(this->_3.m_source == ri.source &&
               this->_3.m_type == ri.type &&
               this->_3.m_key == ri.key) {
                return i;
            }
        }
        return -1;
    }
};

using InputCallbackType = function<void(rawInput ri, float frameDuration)>;

}

#endif //GANESHENGINE_GHINPUTUTILS_H
