#ifndef GANESHENGINE_GHINPUTUTILS_H
#define GANESHENGINE_GHINPUTUTILS_H

#include "ghHeaders.h"
#include <vector>
#include <functional>
#include <GLFW/glfw3.h>

// TODO missing xbox controller keys
// TODO missing mouse button keys
/**
 *This value below are relative to the system input used (GLFW for instance)
 */
// TODO those #define must be conditionnal
#define GH_BUTTON_UNKNOWN           -1

#define GH_BUTTON_MOUSE_1           GLFW_MOUSE_BUTTON_1
#define GH_BUTTON_MOUSE_2           GLFW_MOUSE_BUTTON_2
#define GH_BUTTON_MOUSE_3           GLFW_MOUSE_BUTTON_3
#define GH_BUTTON_MOUSE_4           GLFW_MOUSE_BUTTON_4
#define GH_BUTTON_MOUSE_5           GLFW_MOUSE_BUTTON_5
#define GH_BUTTON_MOUSE_6           GLFW_MOUSE_BUTTON_6
#define GH_BUTTON_MOUSE_7           GLFW_MOUSE_BUTTON_7
#define GH_BUTTON_MOUSE_8           GLFW_MOUSE_BUTTON_8
#define GH_BUTTON_MOUSE_LEFT        GLFW_MOUSE_BUTTON_LEFT
#define GH_BUTTON_MOUSE_RIGHT       GLFW_MOUSE_BUTTON_RIGHT
#define GH_BUTTON_MOUSE_MIDDLE      GLFW_MOUSE_BUTTON_MIDDLE

#define GH_BUTTON_KEY_SPACE         32
#define GH_BUTTON_KEY_APOSTROPHE    39 /* ' */
#define GH_BUTTON_KEY_COMMA         44 /* , */
#define GH_BUTTON_KEY_MINUS         45 /* - */
#define GH_BUTTON_KEY_PERIOD        46 /* . */
#define GH_BUTTON_KEY_SLASH         47 /* / */
#define GH_BUTTON_KEY_0             48
#define GH_BUTTON_KEY_1             49
#define GH_BUTTON_KEY_2             50
#define GH_BUTTON_KEY_3             51
#define GH_BUTTON_KEY_4             52
#define GH_BUTTON_KEY_5             53
#define GH_BUTTON_KEY_6             54
#define GH_BUTTON_KEY_7             55
#define GH_BUTTON_KEY_8             56
#define GH_BUTTON_KEY_9             57
#define GH_BUTTON_KEY_SEMICOLON     59 /* ; */
#define GH_BUTTON_KEY_EQUAL         61 /* = */
#define GH_BUTTON_KEY_A             65
#define GH_BUTTON_KEY_B             66
#define GH_BUTTON_KEY_C             67
#define GH_BUTTON_KEY_D             68
#define GH_BUTTON_KEY_E             69
#define GH_BUTTON_KEY_F             70
#define GH_BUTTON_KEY_G             71
#define GH_BUTTON_KEY_H             72
#define GH_BUTTON_KEY_I             73
#define GH_BUTTON_KEY_J             74
#define GH_BUTTON_KEY_K             75
#define GH_BUTTON_KEY_L             76
#define GH_BUTTON_KEY_M             77
#define GH_BUTTON_KEY_N             78
#define GH_BUTTON_KEY_O             79
#define GH_BUTTON_KEY_P             80
#define GH_BUTTON_KEY_Q             81
#define GH_BUTTON_KEY_R             82
#define GH_BUTTON_KEY_S             83
#define GH_BUTTON_KEY_T             84
#define GH_BUTTON_KEY_U             85
#define GH_BUTTON_KEY_V             86
#define GH_BUTTON_KEY_W             87
#define GH_BUTTON_KEY_X             88
#define GH_BUTTON_KEY_Y             89
#define GH_BUTTON_KEY_Z             90
#define GH_BUTTON_KEY_LEFT_BRACKET  91 /* [ */
#define GH_BUTTON_KEY_BACKSLASH     92 /* \ */
#define GH_BUTTON_KEY_RIGHT_BRACKET 93 /* ] */
#define GH_BUTTON_KEY_GRAVE_ACCENT  96 /* ` */
#define GH_BUTTON_KEY_WORLD_1       161 /* non-US #1 */
#define GH_BUTTON_KEY_WORLD_2       162 /* non-US #2 */
#define GH_BUTTON_KEY_ESCAPE        256
#define GH_BUTTON_KEY_ENTER         257
#define GH_BUTTON_KEY_TAB           258
#define GH_BUTTON_KEY_BACKSPACE     259
#define GH_BUTTON_KEY_INSERT        260
#define GH_BUTTON_KEY_DELETE        261
#define GH_BUTTON_KEY_RIGHT         262
#define GH_BUTTON_KEY_LEFT          263
#define GH_BUTTON_KEY_DOWN          264
#define GH_BUTTON_KEY_UP            265
#define GH_BUTTON_KEY_PAGE_UP       266
#define GH_BUTTON_KEY_PAGE_DOWN     267
#define GH_BUTTON_KEY_HOME          268
#define GH_BUTTON_KEY_END           269
#define GH_BUTTON_KEY_CAPS_LOCK     280
#define GH_BUTTON_KEY_SCROLL_LOCK   281
#define GH_BUTTON_KEY_NUM_LOCK      282
#define GH_BUTTON_KEY_PRINT_SCREEN  283
#define GH_BUTTON_KEY_PAUSE         284
#define GH_BUTTON_KEY_F1            290
#define GH_BUTTON_KEY_F2            291
#define GH_BUTTON_KEY_F3            292
#define GH_BUTTON_KEY_F4            293
#define GH_BUTTON_KEY_F5            294
#define GH_BUTTON_KEY_F6            295
#define GH_BUTTON_KEY_F7            296
#define GH_BUTTON_KEY_F8            297
#define GH_BUTTON_KEY_F9            298
#define GH_BUTTON_KEY_F10           299
#define GH_BUTTON_KEY_F11           300
#define GH_BUTTON_KEY_F12           301
#define GH_BUTTON_KEY_F13           302
#define GH_BUTTON_KEY_F14           303
#define GH_BUTTON_KEY_F15           304
#define GH_BUTTON_KEY_F16           305
#define GH_BUTTON_KEY_F17           306
#define GH_BUTTON_KEY_F18           307
#define GH_BUTTON_KEY_F19           308
#define GH_BUTTON_KEY_F20           309
#define GH_BUTTON_KEY_F21           310
#define GH_BUTTON_KEY_F22           311
#define GH_BUTTON_KEY_F23           312
#define GH_BUTTON_KEY_F24           313
#define GH_BUTTON_KEY_F25           314
#define GH_BUTTON_KEY_KP_0          320
#define GH_BUTTON_KEY_KP_1          321
#define GH_BUTTON_KEY_KP_2          322
#define GH_BUTTON_KEY_KP_3          323
#define GH_BUTTON_KEY_KP_4          324
#define GH_BUTTON_KEY_KP_5          325
#define GH_BUTTON_KEY_KP_6          326
#define GH_BUTTON_KEY_KP_7          327
#define GH_BUTTON_KEY_KP_8          328
#define GH_BUTTON_KEY_KP_9          329
#define GH_BUTTON_KEY_KP_DECIMAL    330
#define GH_BUTTON_KEY_KP_DIVIDE     331
#define GH_BUTTON_KEY_KP_MULTIPLY   332
#define GH_BUTTON_KEY_KP_SUBTRACT   333
#define GH_BUTTON_KEY_KP_ADD        334
#define GH_BUTTON_KEY_KP_ENTER      335
#define GH_BUTTON_KEY_KP_EQUAL      336
#define GH_BUTTON_KEY_LEFT_SHIFT    340
#define GH_BUTTON_KEY_LEFT_CONTROL  341
#define GH_BUTTON_KEY_LEFT_ALT      342
#define GH_BUTTON_KEY_LEFT_SUPER    343
#define GH_BUTTON_KEY_RIGHT_SHIFT   344
#define GH_BUTTON_KEY_RIGHT_CONTROL 345
#define GH_BUTTON_KEY_RIGHT_ALT     346
#define GH_BUTTON_KEY_RIGHT_SUPER   347
#define GH_BUTTON_KEY_MENU          348
#define GH_BUTTON_KEY_LAST          GLFW_KEY_MENU

#define GH_BUTTON_ARRAY_SIZE        350

#define GH_STATE_RELEASED           1
#define GH_STATE_PRESSED            2
#define GH_STATE_HELD               3

#define GH_MAX_JOYSTICK             GLFW_JOYSTICK_LAST

namespace ganeshEngine {

using namespace std;

class Joystick {
public:
	Joystick() {}
	virtual ~Joystick() {}
};

enum class CHORD_SIZE : int {
	_2 = 2,
	_3 = 3
};

class RawInput {
private:
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
	enum class SOURCE {
		MOUSE,
		KEYBOARD,
		JOYSTICK
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
	enum class TYPE {
		PRESS,
		DOWN,
		RELEASE,
		RANGE,
		MOVE
	};

	/**
	 * Every supported key/button which could be pressed, released or held
	 * Note this enum regroup regardless keyboard's key, mouse's button as
	 * well as gamepad's button
	 */
	enum class KEY : int {
		MOUSE_LEFT = GH_BUTTON_MOUSE_LEFT,
		MOUSE_RIGHT = GH_BUTTON_MOUSE_RIGHT,
		APOSTROPHE = GH_BUTTON_KEY_APOSTROPHE,
		COMMA = GH_BUTTON_KEY_COMMA,
		MINUS = GH_BUTTON_KEY_MINUS,
		PERIOD = GH_BUTTON_KEY_PERIOD,
		SLASH = GH_BUTTON_KEY_SLASH,
		NUM_0 = GH_BUTTON_KEY_0,
		NUM_1 = GH_BUTTON_KEY_1,
		NUM_2 = GH_BUTTON_KEY_2,
		NUM_3 = GH_BUTTON_KEY_3,
		NUM_4 = GH_BUTTON_KEY_4,
		NUM_5 = GH_BUTTON_KEY_5,
		NUM_6 = GH_BUTTON_KEY_6,
		NUM_7 = GH_BUTTON_KEY_7,
		NUM_8 = GH_BUTTON_KEY_8,
		NUM_9 = GH_BUTTON_KEY_9,
		SEMICOLON = GH_BUTTON_KEY_SEMICOLON,
		EQUAL = GH_BUTTON_KEY_EQUAL,
		SPACE = GH_BUTTON_KEY_SPACE,
		A = GH_BUTTON_KEY_A,
		B = GH_BUTTON_KEY_B,
		C = GH_BUTTON_KEY_C,
		D = GH_BUTTON_KEY_D,
		E = GH_BUTTON_KEY_E,
		F = GH_BUTTON_KEY_F,
		G = GH_BUTTON_KEY_G,
		H = GH_BUTTON_KEY_H,
		I = GH_BUTTON_KEY_I,
		J = GH_BUTTON_KEY_J,
		K = GH_BUTTON_KEY_K,
		L = GH_BUTTON_KEY_L,
		M = GH_BUTTON_KEY_M,
		N = GH_BUTTON_KEY_N,
		O = GH_BUTTON_KEY_O,
		P = GH_BUTTON_KEY_P,
		Q = GH_BUTTON_KEY_Q,
		R = GH_BUTTON_KEY_R,
		S = GH_BUTTON_KEY_S,
		T = GH_BUTTON_KEY_T,
		U = GH_BUTTON_KEY_U,
		V = GH_BUTTON_KEY_V,
		W = GH_BUTTON_KEY_W,
		X = GH_BUTTON_KEY_X,
		Y = GH_BUTTON_KEY_Y,
		Z = GH_BUTTON_KEY_Z,
		LEFT_BRACKET = GH_BUTTON_KEY_LEFT_BRACKET,
		BACKSLASH = GH_BUTTON_KEY_BACKSLASH,
		RIGHT_BRACKET = GH_BUTTON_KEY_RIGHT_BRACKET,
		GRAVE_ACCENT = GH_BUTTON_KEY_GRAVE_ACCENT,
		WORLD_1 = GH_BUTTON_KEY_WORLD_1,
		WORLD_2 = GH_BUTTON_KEY_WORLD_2,
		ESCAPE = GH_BUTTON_KEY_ESCAPE,
		ENTER = GH_BUTTON_KEY_ENTER,
		TAB = GH_BUTTON_KEY_TAB,
		BACKSPACE = GH_BUTTON_KEY_BACKSPACE,
		INSERT = GH_BUTTON_KEY_INSERT,
		DELETE = GH_BUTTON_KEY_DELETE,
		RIGHT = GH_BUTTON_KEY_RIGHT,
		LEFT = GH_BUTTON_KEY_LEFT,
		DOWN = GH_BUTTON_KEY_DOWN,
		UP = GH_BUTTON_KEY_UP,
		PAGE_UP = GH_BUTTON_KEY_PAGE_UP,
		PAGE_DOWN = GH_BUTTON_KEY_PAGE_DOWN,
		HOME = GH_BUTTON_KEY_HOME,
		END = GH_BUTTON_KEY_END,
		CAPS_LOCK = GH_BUTTON_KEY_CAPS_LOCK,
		SCROLL_LOCK = GH_BUTTON_KEY_SCROLL_LOCK,
		NUM_LOCK = GH_BUTTON_KEY_NUM_LOCK,
		PRINT_SCREEN = GH_BUTTON_KEY_PRINT_SCREEN,
		PAUSE = GH_BUTTON_KEY_PAUSE,
		F1 = GH_BUTTON_KEY_F1,
		F2 = GH_BUTTON_KEY_F2,
		F3 = GH_BUTTON_KEY_F3,
		F4 = GH_BUTTON_KEY_F4,
		F5 = GH_BUTTON_KEY_F5,
		F6 = GH_BUTTON_KEY_F6,
		F7 = GH_BUTTON_KEY_F7,
		F8 = GH_BUTTON_KEY_F8,
		F9 = GH_BUTTON_KEY_F9,
		F10 = GH_BUTTON_KEY_F10,
		F11 = GH_BUTTON_KEY_F11,
		F12 = GH_BUTTON_KEY_F12,
		F13 = GH_BUTTON_KEY_F13,
		F14 = GH_BUTTON_KEY_F14,
		F15 = GH_BUTTON_KEY_F15,
		F16 = GH_BUTTON_KEY_F16,
		F17 = GH_BUTTON_KEY_F17,
		F18 = GH_BUTTON_KEY_F18,
		F19 = GH_BUTTON_KEY_F19,
		F20 = GH_BUTTON_KEY_F20,
		F21 = GH_BUTTON_KEY_F21,
		F22 = GH_BUTTON_KEY_F22,
		F23 = GH_BUTTON_KEY_F23,
		F24 = GH_BUTTON_KEY_F24,
		F25 = GH_BUTTON_KEY_F25,
		KP_0 = GH_BUTTON_KEY_KP_0,
		KP_1 = GH_BUTTON_KEY_KP_1,
		KP_2 = GH_BUTTON_KEY_KP_2,
		KP_3 = GH_BUTTON_KEY_KP_3,
		KP_4 = GH_BUTTON_KEY_KP_4,
		KP_5 = GH_BUTTON_KEY_KP_5,
		KP_6 = GH_BUTTON_KEY_KP_6,
		KP_7 = GH_BUTTON_KEY_KP_7,
		KP_8 = GH_BUTTON_KEY_KP_8,
		KP_9 = GH_BUTTON_KEY_KP_9,
		KP_DECIMAL = GH_BUTTON_KEY_KP_DECIMAL,
		KP_DIVIDE = GH_BUTTON_KEY_KP_DIVIDE,
		KP_MULTIPLY = GH_BUTTON_KEY_KP_MULTIPLY,
		KP_SUBTRACT = GH_BUTTON_KEY_KP_SUBTRACT,
		KP_ADD = GH_BUTTON_KEY_KP_ADD,
		KP_ENTER = GH_BUTTON_KEY_KP_ENTER,
		KP_EQUAL = GH_BUTTON_KEY_KP_EQUAL,
		LEFT_SHIFT = GH_BUTTON_KEY_LEFT_SHIFT,
		LEFT_CONTROL = GH_BUTTON_KEY_LEFT_CONTROL,
		LEFT_ALT = GH_BUTTON_KEY_LEFT_ALT,
		LEFT_SUPER = GH_BUTTON_KEY_LEFT_SUPER,
		RIGHT_SHIFT = GH_BUTTON_KEY_RIGHT_SHIFT,
		RIGHT_CONTROL = GH_BUTTON_KEY_RIGHT_CONTROL,
		RIGHT_ALT = GH_BUTTON_KEY_RIGHT_ALT,
		RIGHT_SUPER = GH_BUTTON_KEY_RIGHT_SUPER,
		MENU = GH_BUTTON_KEY_MENU
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

/**
 * Store informations for all inputs that can be either pressed,
 * released, or held (like keyboard keys, joysticks buttons or
 * mouse buttons)
 */
typedef struct buttonData_s {
	int key;
	int scancode;
	int mods;
	long duration;
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
	/**
	 * From which device the input comes from
	 */
	RawInput::SOURCE source;

	/**
	 * Type of the received input
	 */
	RawInput::TYPE type;

	/**
	 * Time when input occured
	 */
	long timestamp;

	/**
	 * Index of the devices that generates the input
	 *
	 * @note will be unrelevant value for the keyboard or the mouse
	 * device source but significant when multiple xbox controllers are
	 * plugged in
	 */
	int idx;

	/**
	 * Payload informations
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
private:
	RawInput::SOURCE m_source;
	RawInput::TYPE m_type;
	RawInput::KEY m_key;
	U32 m_callbackNameHash;

public:
	InputMatch(RawInput::SOURCE source, RawInput::TYPE type, RawInput::KEY key, U32 callbackHash) :
			m_source(source), m_type(type), m_key(key), m_callbackNameHash(callbackHash) {}

	RawInput::SOURCE getSource() const;
	RawInput::TYPE getType() const;
	RawInput::KEY getKey() const;
	U32 getCallbackHash() const;
};

/**
 *
 */
class Chord {
public:
	CHORD_SIZE size;
	shared_ptr<InputMatch> _1{nullptr};
	shared_ptr<InputMatch> _2{nullptr};
	shared_ptr<InputMatch> _3{nullptr};
	U32 callbackNameHash;
};


}

#endif //GANESHENGINE_GHINPUTUTILS_H
