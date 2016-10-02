#ifndef GANESHENGINE_GHINPUTUTILS_H
#define GANESHENGINE_GHINPUTUTILS_H

#include <ghTypes.hpp>
#include <util/ghStringId.hpp>

#include <vector>
#include <cstring>
#include <functional>

#define GH_DETECTION_DURATION_SECOND 0.02f
#define GH_KEYBOARD_KEY_COUNT       120
#define GH_MOUSE_KEY_COUNT          8

namespace ganeshEngine {

using namespace std;

/**
 * List of device providing input that the engine can deal with
 */
enum class InputSource : U8 {
	MOUSE 		= 0x01,
	KEYBOARD 	= 0x02,
	DEVICE 		= 0x03
};

/**
 * Kind of input handled by the engine.
 * Axis is used to handle range like joystick movement, mouse movement or triggers on the xbox controller
 */
enum class InputType : U8 {
	BUTTON_UP 		= 0x01,
	BUTTON_PRESS 	= 0x02,
	BUTTON_DOWN 	= 0x03,
	BUTTON_RELEASE	= 0x04,
	AXIS			= 0x05,
};

/**
 * Every supported key code for button related input. Basically if the input could be pressed, held and released, it has
 * an entry here is it's handled by the engine
 * @note NONE value dedicated to event type which are not button related
 */
enum class InputCode : U32 {
	NONE						= 0x00000000,
	UNSUPPORTED					= 0xFFFFFFFF,

	KEYBOARD_F1 				= 0x01000001,
	KEYBOARD_F2 				= 0x01000002,
	KEYBOARD_F3 				= 0x01000003,
	KEYBOARD_F4 				= 0x01000004,
	KEYBOARD_F5 				= 0x01000005,
	KEYBOARD_F6 				= 0x01000006,
	KEYBOARD_F7 				= 0x01000007,
	KEYBOARD_F8 				= 0x01000008,
	KEYBOARD_F9 				= 0x01000009,
	KEYBOARD_F10 				= 0x0100000A,
	KEYBOARD_F11 				= 0x0100000B,
	KEYBOARD_F12 				= 0x0100000C,
	KEYBOARD_F13 				= 0x0100000D,
	KEYBOARD_F14 				= 0x0100000E,
	KEYBOARD_F15 				= 0x0100000F,
	KEYBOARD_F16 				= 0x01000010,
	KEYBOARD_F17 				= 0x01000011,
	KEYBOARD_F18 				= 0x01000012,
	KEYBOARD_F19 				= 0x01000013,
	KEYBOARD_F20 				= 0x01000014,
	KEYBOARD_F21 				= 0x01000015,
	KEYBOARD_F22 				= 0x01000016,
	KEYBOARD_F23 				= 0x01000017,
	KEYBOARD_F24 				= 0x01000018,
	KEYBOARD_F25 				= 0x01000019,
	KEYBOARD_SPACE 				= 0x0100001A,
	KEYBOARD_APOSTROPHE 		= 0x0100001B,
	KEYBOARD_COMMA 				= 0x0100001C,
	KEYBOARD_MINUS 				= 0x0100001D,
	KEYBOARD_PERIOD 			= 0x0100001E,
	KEYBOARD_SLASH 				= 0x0100001F,
	KEYBOARD_0 					= 0x01000020,
	KEYBOARD_1 					= 0x01000021,
	KEYBOARD_2 					= 0x01000022,
	KEYBOARD_3 					= 0x01000023,
	KEYBOARD_4 					= 0x01000024,
	KEYBOARD_5 					= 0x01000025,
	KEYBOARD_6 					= 0x01000026,
	KEYBOARD_7 					= 0x01000027,
	KEYBOARD_8 					= 0x01000028,
	KEYBOARD_9 					= 0x01000029,
	KEYBOARD_KP_0 				= 0x0100002A,
	KEYBOARD_KP_1 				= 0x0100002B,
	KEYBOARD_KP_2 				= 0x0100002C,
	KEYBOARD_KP_3 				= 0x0100002D,
	KEYBOARD_KP_4 				= 0x0100002E,
	KEYBOARD_KP_5 				= 0x0100002F,
	KEYBOARD_KP_6 				= 0x01000030,
	KEYBOARD_KP_7 				= 0x01000031,
	KEYBOARD_KP_8 				= 0x01000032,
	KEYBOARD_KP_9 				= 0x01000033,
	KEYBOARD_SEMICOLON 			= 0x01000034,
	KEYBOARD_EQUAL 				= 0x01000035,
	KEYBOARD_A 					= 0x01000036,
	KEYBOARD_B 					= 0x01000037,
	KEYBOARD_C 					= 0x01000038,
	KEYBOARD_D 					= 0x01000039,
	KEYBOARD_E 					= 0x0100003A,
	KEYBOARD_F 					= 0x0100003B,
	KEYBOARD_G 					= 0x0100003C,
	KEYBOARD_H 					= 0x0100003D,
	KEYBOARD_I 					= 0x0100003E,
	KEYBOARD_J 					= 0x0100003F,
	KEYBOARD_K 					= 0x01000040,
	KEYBOARD_L 					= 0x01000041,
	KEYBOARD_M 					= 0x01000042,
	KEYBOARD_N 					= 0x01000043,
	KEYBOARD_O 					= 0x01000044,
	KEYBOARD_P 					= 0x01000045,
	KEYBOARD_Q 					= 0x01000046,
	KEYBOARD_R 					= 0x01000047,
	KEYBOARD_S 					= 0x01000048,
	KEYBOARD_T 					= 0x01000049,
	KEYBOARD_U 					= 0x0100004A,
	KEYBOARD_V 					= 0x0100004B,
	KEYBOARD_W 					= 0x0100004C,
	KEYBOARD_X 					= 0x0100004D,
	KEYBOARD_Y 					= 0x0100004E,
	KEYBOARD_Z 					= 0x0100004F,
	KEYBOARD_LEFT_BRACKET 		= 0x01000050,
	KEYBOARD_BACKSLASH 			= 0x01000051,
	KEYBOARD_RIGHT_BRACKET 		= 0x01000052,
	KEYBOARD_GRAVE_ACCENT 		= 0x01000053,
	KEYBOARD_WORLD_1 			= 0x01000054,
	KEYBOARD_WORLD_2 			= 0x01000055,
	KEYBOARD_ESCAPE 			= 0x01000056,
	KEYBOARD_ENTER 				= 0x01000057,
	KEYBOARD_TAB 				= 0x01000058,
	KEYBOARD_BACKSPACE 			= 0x01000059,
	KEYBOARD_INSERT 			= 0x0100005A,
	KEYBOARD_DELETE 			= 0x0100005B,
	KEYBOARD_RIGHT 				= 0x0100005C,
	KEYBOARD_LEFT 				= 0x0100005D,
	KEYBOARD_DOWN 				= 0x0100005E,
	KEYBOARD_UP 				= 0x0100005F,
	KEYBOARD_PAGE_UP 			= 0x01000060,
	KEYBOARD_PAGE_DOWN 			= 0x01000061,
	KEYBOARD_HOME 				= 0x01000062,
	KEYBOARD_END 				= 0x01000063,
	KEYBOARD_CAPS_LOCK 			= 0x01000064,
	KEYBOARD_SCROLL_LOCK 		= 0x01000065,
	KEYBOARD_NUM_LOCK 			= 0x01000066,
	KEYBOARD_PRINT_SCREEN 		= 0x01000067,
	KEYBOARD_PAUSE 				= 0x01000068,
	KEYBOARD_KP_DECIMAL 		= 0x01000069,
	KEYBOARD_KP_DIVIDE 			= 0x0100006A,
	KEYBOARD_KP_MULTIPLY 		= 0x0100006B,
	KEYBOARD_KP_SUBTRACT 		= 0x0100006C,
	KEYBOARD_KP_ADD 			= 0x0100006D,
	KEYBOARD_KP_ENTER 			= 0x0100006E,
	KEYBOARD_KP_EQUAL 			= 0x0100006F,
	KEYBOARD_LEFT_SHIFT 		= 0x01000070,
	KEYBOARD_LEFT_CONTROL 		= 0x01000071,
	KEYBOARD_LEFT_ALT 			= 0x01000072,
	KEYBOARD_LEFT_SUPER 		= 0x01000073,
	KEYBOARD_RIGHT_SHIFT 		= 0x01000074,
	KEYBOARD_RIGHT_CONTROL 		= 0x01000075,
	KEYBOARD_RIGHT_ALT 			= 0x01000076,
	KEYBOARD_RIGHT_SUPER 		= 0x01000077,
	KEYBOARD_MENU 				= 0x01000078,
	MOUSE_BUTTON_1 				= 0x02000011,
	MOUSE_BUTTON_2 				= 0x02000012,
	MOUSE_BUTTON_3 				= 0x02000013,
	MOUSE_BUTTON_4 				= 0x02000014,
	MOUSE_BUTTON_5 				= 0x02000015,
	MOUSE_BUTTON_6 				= 0x02000016,
	MOUSE_BUTTON_7 				= 0x02000017,
	MOUSE_BUTTON_8 				= 0x02000018,
	MOUSE_LEFT 					= 0x02000011,
	MOUSE_RIGHT 				= 0x02000012,
	MOUSE_MIDDLE				= 0x02000013,
	XBOX_CONTROLLER_A 			= 0x03000001,
	XBOX_CONTROLLER_B 			= 0x03000002,
	XBOX_CONTROLLER_X 			= 0x03000003,
	XBOX_CONTROLLER_Y 			= 0x03000004,
	XBOX_CONTROLLER_START		= 0x03000005,
	XBOX_CONTROLLER_SELECT		= 0x03000006,
	XBOX_CONTROLLER_MENU		= 0x03000007,
	XBOX_CONTROLLER_RS			= 0x03000008,
	XBOX_CONTROLLER_LS			= 0x03000009,
	XBOX_CONTROLLER_UP			= 0x0300000A,
	XBOX_CONTROLLER_DOWN		= 0x0300000B,
	XBOX_CONTROLLER_LEFT		= 0x0300000C,
	XBOX_CONTROLLER_RIGHT		= 0x0300000D,
    XBOX_CONTROLLER_LB          = 0x0300000E,
    XBOX_CONTROLLER_RB          = 0x0300000F,
	XBOX_CONTROLLER_AXIS_LEFT_X	= 0x03000010,
	XBOX_CONTROLLER_AXIS_LEFT_Y	= 0x03000011,
    XBOX_CONTROLLER_AXIS_RIGHT_X= 0x03000012,
    XBOX_CONTROLLER_AXIS_RIGHT_Y= 0x03000013,
    XBOX_CONTROLLER_AXIS_RT     = 0x03000014,
    XBOX_CONTROLLER_AXIS_LT     = 0x03000015
};

/**
 * Chord is a combination of two or three inputs occuring at the (almost) same time, which is resulting to one action in
 * the game
 */
enum class InputChordSize : U8 {
	_2 = 2,
	_3 = 3
};

/**
 * Each input can be contextualized with one of those modifier keys/combination
 */
enum class InputModifier : U8 {
	CTRL			= 0x01,
	SHIFT			= 0x02,
	CTRL_SHIFT		= 0x03,
	ALT				= 0x04,
	CTRL_ALT		= 0x05,
	ALT_SHIFT		= 0x06
};

namespace inputDetails {

const char* const undefined 					= "UNDEFINED";

const char* const sourceMouse 					= "MOUSE";
const char* const sourceKeyboard 				= "KEYBOARD";
const char* const sourceDevice	 				= "DEVICE";

const char* const typeUp 						= "BUTTON_UP";
const char* const typePress 					= "BUTTON_PRESS";
const char* const typeRelease 					= "BUTTON_RELEASE";
const char* const typeDown 						= "BUTTON_DOWN";
const char* const typeAxis 						= "AXIS";

const char* const NONE							= "NONE";
const char* const UNSUPPORTED 					= "UNSUPPORTED";
const char* const KEYBOARD_F1 					= "KEYBOARD_F1";
const char* const KEYBOARD_F2 					= "KEYBOARD_F2";
const char* const KEYBOARD_F3 					= "KEYBOARD_F3";
const char* const KEYBOARD_F4 					= "KEYBOARD_F4";
const char* const KEYBOARD_F5 					= "KEYBOARD_F5";
const char* const KEYBOARD_F6 					= "KEYBOARD_F6";
const char* const KEYBOARD_F7 					= "KEYBOARD_F7";
const char* const KEYBOARD_F8 					= "KEYBOARD_F8";
const char* const KEYBOARD_F9 					= "KEYBOARD_F9";
const char* const KEYBOARD_F10 					= "KEYBOARD_F10";
const char* const KEYBOARD_F11 					= "KEYBOARD_F11";
const char* const KEYBOARD_F12 					= "KEYBOARD_F12";
const char* const KEYBOARD_F13 					= "KEYBOARD_F13";
const char* const KEYBOARD_F14 					= "KEYBOARD_F14";
const char* const KEYBOARD_F15 					= "KEYBOARD_F15";
const char* const KEYBOARD_F16 					= "KEYBOARD_F16";
const char* const KEYBOARD_F17 					= "KEYBOARD_F17";
const char* const KEYBOARD_F18 					= "KEYBOARD_F18";
const char* const KEYBOARD_F19 					= "KEYBOARD_F19";
const char* const KEYBOARD_F20 					= "KEYBOARD_F20";
const char* const KEYBOARD_F21 					= "KEYBOARD_F21";
const char* const KEYBOARD_F22 					= "KEYBOARD_F22";
const char* const KEYBOARD_F23 					= "KEYBOARD_F23";
const char* const KEYBOARD_F24 					= "KEYBOARD_F24";
const char* const KEYBOARD_F25 					= "KEYBOARD_F25";
const char* const KEYBOARD_SPACE 				= "KEYBOARD_SPACE";
const char* const KEYBOARD_APOSTROPHE 			= "KEYBOARD_APOSTROPHE";
const char* const KEYBOARD_COMMA 				= "KEYBOARD_COMMA";
const char* const KEYBOARD_MINUS 				= "KEYBOARD_MINUS";
const char* const KEYBOARD_PERIOD 				= "KEYBOARD_PERIOD";
const char* const KEYBOARD_SLASH 				= "KEYBOARD_SLASH";
const char* const KEYBOARD_0 					= "KEYBOARD_0";
const char* const KEYBOARD_1 					= "KEYBOARD_1";
const char* const KEYBOARD_2 					= "KEYBOARD_2";
const char* const KEYBOARD_3 					= "KEYBOARD_3";
const char* const KEYBOARD_4 					= "KEYBOARD_4";
const char* const KEYBOARD_5 					= "KEYBOARD_5";
const char* const KEYBOARD_6 					= "KEYBOARD_6";
const char* const KEYBOARD_7 					= "KEYBOARD_7";
const char* const KEYBOARD_8 					= "KEYBOARD_8";
const char* const KEYBOARD_9 					= "KEYBOARD_9";
const char* const KEYBOARD_KP_0 				= "KEYBOARD_KP_0";
const char* const KEYBOARD_KP_1 				= "KEYBOARD_KP_1";
const char* const KEYBOARD_KP_2 				= "KEYBOARD_KP_2";
const char* const KEYBOARD_KP_3 				= "KEYBOARD_KP_3";
const char* const KEYBOARD_KP_4 				= "KEYBOARD_KP_4";
const char* const KEYBOARD_KP_5 				= "KEYBOARD_KP_5";
const char* const KEYBOARD_KP_6 				= "KEYBOARD_KP_6";
const char* const KEYBOARD_KP_7 				= "KEYBOARD_KP_7";
const char* const KEYBOARD_KP_8 				= "KEYBOARD_KP_8";
const char* const KEYBOARD_KP_9 				= "KEYBOARD_KP_9";
const char* const KEYBOARD_SEMICOLON 			= "KEYBOARD_SEMICOLON";
const char* const KEYBOARD_EQUAL 				= "KEYBOARD_EQUAL";
const char* const KEYBOARD_A 					= "KEYBOARD_A";
const char* const KEYBOARD_B 					= "KEYBOARD_B";
const char* const KEYBOARD_C 					= "KEYBOARD_C";
const char* const KEYBOARD_D 					= "KEYBOARD_D";
const char* const KEYBOARD_E 					= "KEYBOARD_E";
const char* const KEYBOARD_F 					= "KEYBOARD_F";
const char* const KEYBOARD_G 					= "KEYBOARD_G";
const char* const KEYBOARD_H 					= "KEYBOARD_H";
const char* const KEYBOARD_I 					= "KEYBOARD_I";
const char* const KEYBOARD_J 					= "KEYBOARD_J";
const char* const KEYBOARD_K 					= "KEYBOARD_K";
const char* const KEYBOARD_L 					= "KEYBOARD_L";
const char* const KEYBOARD_M 					= "KEYBOARD_M";
const char* const KEYBOARD_N 					= "KEYBOARD_N";
const char* const KEYBOARD_O 					= "KEYBOARD_O";
const char* const KEYBOARD_P 					= "KEYBOARD_P";
const char* const KEYBOARD_Q 					= "KEYBOARD_Q";
const char* const KEYBOARD_R 					= "KEYBOARD_R";
const char* const KEYBOARD_S 					= "KEYBOARD_S";
const char* const KEYBOARD_T 					= "KEYBOARD_T";
const char* const KEYBOARD_U 					= "KEYBOARD_U";
const char* const KEYBOARD_V 					= "KEYBOARD_V";
const char* const KEYBOARD_W 					= "KEYBOARD_W";
const char* const KEYBOARD_X 					= "KEYBOARD_X";
const char* const KEYBOARD_Y 					= "KEYBOARD_Y";
const char* const KEYBOARD_Z 					= "KEYBOARD_Z";
const char* const KEYBOARD_LEFT_BRACKET 		= "KEYBOARD_LEFT_BRACKET";
const char* const KEYBOARD_BACKSLASH 			= "KEYBOARD_BACKSLASH";
const char* const KEYBOARD_RIGHT_BRACKET 		= "KEYBOARD_RIGHT_BRACKET";
const char* const KEYBOARD_GRAVE_ACCENT 		= "KEYBOARD_GRAVE_ACCENT";
const char* const KEYBOARD_WORLD_1 				= "KEYBOARD_WORLD_1";
const char* const KEYBOARD_WORLD_2 				= "KEYBOARD_WORLD_2";
const char* const KEYBOARD_ESCAPE 				= "KEYBOARD_ESCAPE";
const char* const KEYBOARD_ENTER 				= "KEYBOARD_ENTER";
const char* const KEYBOARD_TAB 					= "KEYBOARD_TAB";
const char* const KEYBOARD_BACKSPACE 			= "KEYBOARD_BACKSPACE";
const char* const KEYBOARD_INSERT 				= "KEYBOARD_INSERT";
const char* const KEYBOARD_DELETE 				= "KEYBOARD_DELETE";
const char* const KEYBOARD_RIGHT 				= "KEYBOARD_RIGHT";
const char* const KEYBOARD_LEFT 				= "KEYBOARD_LEFT";
const char* const KEYBOARD_DOWN 				= "KEYBOARD_DOWN";
const char* const KEYBOARD_UP 					= "KEYBOARD_UP";
const char* const KEYBOARD_PAGE_UP 				= "KEYBOARD_PAGE_UP";
const char* const KEYBOARD_PAGE_DOWN 			= "KEYBOARD_PAGE_DOWN";
const char* const KEYBOARD_HOME 				= "KEYBOARD_HOME";
const char* const KEYBOARD_END 					= "KEYBOARD_END";
const char* const KEYBOARD_CAPS_LOCK 			= "KEYBOARD_CAPS_LOCK";
const char* const KEYBOARD_SCROLL_LOCK 			= "KEYBOARD_SCROLL_LOCK";
const char* const KEYBOARD_NUM_LOCK 			= "KEYBOARD_NUM_LOCK";
const char* const KEYBOARD_PRINT_SCREEN 		= "KEYBOARD_PRINT_SCREEN";
const char* const KEYBOARD_PAUSE 				= "KEYBOARD_PAUSE";
const char* const KEYBOARD_KP_DECIMAL 			= "KEYBOARD_KP_DECIMAL";
const char* const KEYBOARD_KP_DIVIDE 			= "KEYBOARD_KP_DIVIDE";
const char* const KEYBOARD_KP_MULTIPLY 			= "KEYBOARD_KP_MULTIPLY";
const char* const KEYBOARD_KP_SUBTRACT 			= "KEYBOARD_KP_SUBTRACT";
const char* const KEYBOARD_KP_ADD 				= "KEYBOARD_KP_ADD";
const char* const KEYBOARD_KP_ENTER 			= "KEYBOARD_KP_ENTER";
const char* const KEYBOARD_KP_EQUAL 			= "KEYBOARD_KP_EQUAL";
const char* const KEYBOARD_LEFT_SHIFT 			= "KEYBOARD_LEFT_SHIFT";
const char* const KEYBOARD_LEFT_CONTROL 		= "KEYBOARD_LEFT_CONTROL";
const char* const KEYBOARD_LEFT_ALT 			= "KEYBOARD_LEFT_ALT";
const char* const KEYBOARD_LEFT_SUPER 			= "KEYBOARD_LEFT_SUPER";
const char* const KEYBOARD_RIGHT_SHIFT 			= "KEYBOARD_RIGHT_SHIFT";
const char* const KEYBOARD_RIGHT_CONTROL 		= "KEYBOARD_RIGHT_CONTROL";
const char* const KEYBOARD_RIGHT_ALT 			= "KEYBOARD_RIGHT_ALT";
const char* const KEYBOARD_RIGHT_SUPER 			= "KEYBOARD_RIGHT_SUPER";
const char* const KEYBOARD_MENU 				= "KEYBOARD_MENU";
const char* const MOUSE_BUTTON_1 				= "MOUSE_BUTTON_1";
const char* const MOUSE_BUTTON_2 				= "MOUSE_BUTTON_2";
const char* const MOUSE_BUTTON_3 				= "MOUSE_BUTTON_3";
const char* const MOUSE_BUTTON_4 				= "MOUSE_BUTTON_4";
const char* const MOUSE_BUTTON_5 				= "MOUSE_BUTTON_5";
const char* const MOUSE_BUTTON_6 				= "MOUSE_BUTTON_6";
const char* const MOUSE_BUTTON_7 				= "MOUSE_BUTTON_7";
const char* const MOUSE_BUTTON_8 				= "MOUSE_BUTTON_8";
const char* const MOUSE_LEFT 					= "MOUSE_LEFT";
const char* const MOUSE_RIGHT 					= "MOUSE_RIGHT";
const char* const MOUSE_MIDDLE					= "MOUSE_MIDDLE";
const char* const XBOX_CONTROLLER_A 			= "XBOX_CONTROLLER_A";
const char* const XBOX_CONTROLLER_B 			= "XBOX_CONTROLLER_B";
const char* const XBOX_CONTROLLER_X 			= "XBOX_CONTROLLER_X";
const char* const XBOX_CONTROLLER_Y 			= "XBOX_CONTROLLER_Y";
const char* const XBOX_CONTROLLER_START			= "XBOX_CONTROLLER_START";
const char* const XBOX_CONTROLLER_SELECT		= "XBOX_CONTROLLER_SELECT";
const char* const XBOX_CONTROLLER_MENU			= "XBOX_CONTROLLER_MENU";
const char* const XBOX_CONTROLLER_RS			= "XBOX_CONTROLLER_RS";
const char* const XBOX_CONTROLLER_LS			= "XBOX_CONTROLLER_LS";
const char* const XBOX_CONTROLLER_RB			= "XBOX_CONTROLLER_RB";
const char* const XBOX_CONTROLLER_LB			= "XBOX_CONTROLLER_LB";
const char* const XBOX_CONTROLLER_UP			= "XBOX_CONTROLLER_UP";
const char* const XBOX_CONTROLLER_DOWN			= "XBOX_CONTROLLER_DOWN";
const char* const XBOX_CONTROLLER_LEFT			= "XBOX_CONTROLLER_LEFT";
const char* const XBOX_CONTROLLER_RIGHT			= "XBOX_CONTROLLER_RIGHT";
const char* const XBOX_CONTROLLER_AXIS_LEFT_X	= "XBOX_CONTROLLER_AXIS_LEFT_X";
const char* const XBOX_CONTROLLER_AXIS_LEFT_Y	= "XBOX_CONTROLLER_AXIS_LEFT_Y";
const char* const XBOX_CONTROLLER_AXIS_RIGHT_X	= "XBOX_CONTROLLER_AXIS_RIGHT_X";
const char* const XBOX_CONTROLLER_AXIS_RIGHT_Y	= "XBOX_CONTROLLER_AXIS_RIGHT_Y";
const char* const XBOX_CONTROLLER_AXIS_RT       = "XBOX_CONTROLLER_AXIS_RT";
const char* const XBOX_CONTROLLER_AXIS_LT       = "XBOX_CONTROLLER_AXIS_LT";

template<typename K>
K fromString(const char *value);

template<typename K>
const char *toString(K value);

bool isKeyboardCode(const InputCode code);

bool isMouseCode(const InputCode code);

bool isDeviceCode(const InputCode code);

}

/**
 * Store informations from an input read from the system input layer, and throughout the inputManager
 */
class RawInput {
public:
	/** Index of the devices that generates the input
	 *
	 * @note will be unrelevant value for the keyboard or the mouse
	 * device source but significant when multiple xbox controllers are
	 * plugged in
	 */
	U32 idx;

	/** From which device the input comes from
	 */
	InputSource source;

	/** Type of the received input
	 */
	InputType type;

	/** Key of the received input, could be set with NONE value
	 * for certain kind of input
	 */
	InputCode code;

	/** No effect at this time
	 */
	InputModifier modifiers;

	F32 chordDetectionLifetimeS = GH_DETECTION_DURATION_SECOND;

	/** Store informations for all inputs that can be either pressed,
	 * released, or held (like keyboard keys, joysticks buttons or
	 * mouse buttons)
	 */
	union datas_u {
		struct buttonData_s {
			F32 holdDurationSecond;
		} button;

		struct rangeData_s {
			F32 x;
			F32 y;
			F32 z;
		} axis;
	} data;

};

/**
 *
 */
class InputMatch {
public:
	InputSource m_source;
	InputType m_type;
	InputCode m_code;
	stringId m_callbackId;

	InputMatch() {}

	InputMatch(InputSource source, InputType type, InputCode code, stringId callbackId) :
			m_source(source),
			m_type(type),
			m_code(code),
			m_callbackId(callbackId) {}

	bool isMatch(const RawInput& rawInput) const {
		if(rawInput.source == m_source && rawInput.type == m_type) {
			if(m_code != InputCode::NONE) {
				return (rawInput.code == m_code);
			}
			return true;
		}
		return false;
	}

	bool equals(const InputMatch& inputMatch) const {
		return (this->m_source == inputMatch.m_source &&
			this->m_type == inputMatch.m_type &&
			this->m_code == inputMatch.m_code);
	}
};

/**
 *
 */
class Chord {
public:
	InputChordSize size;
	InputMatch _1;
	InputMatch _2;
	InputMatch _3;
	stringId m_callbackNameHash;

public:
	Chord(stringId callbackNameHash, InputMatch i1, InputMatch i2) :
			size(InputChordSize::_2),
			_1(i1), _2(i2),
			m_callbackNameHash(callbackNameHash) {}

	Chord(stringId callbackNameHash, InputMatch i1, InputMatch i2, InputMatch i3) :
			size(InputChordSize::_3),
			_1(i1), _2(i2), _3(i3),
			m_callbackNameHash(callbackNameHash) {}

    bool containsRawInput(InputSource source, InputType type, InputCode code) const {
        if(size == InputChordSize::_3) {
            return ((_1.m_source == source && _1.m_type == type && _1.m_code == code) ||
                    (_2.m_source == source && _2.m_type == type && _2.m_code == code) ||
                    (_3.m_source == source && _3.m_type == type && _3.m_code == code));
        } else if(size == InputChordSize::_2) {
            return ((_1.m_source == source && _1.m_type == type && _1.m_code == code) ||
                    (_2.m_source == source && _2.m_type == type && _2.m_code == code));
        }
        return false;
    }

    int findFirstInputFrom(vector<RawInput> &listInputs) const {
        for(U32 i = 0 ; i<listInputs.size() ; ++i) {
            auto const& ri = listInputs[i];
            if(this->_1.m_source == ri.source &&
               this->_1.m_type == ri.type &&
               this->_1.m_code == ri.code) {
                return i;
            }
        }
        return -1;
    }

    int findSecondInputFrom(vector<RawInput> &listInputs) const {
        for(U32 i = 0 ; i<listInputs.size() ; ++i) {
            auto const& ri = listInputs[i];
            if(this->_2.m_source == ri.source &&
               this->_2.m_type == ri.type &&
               this->_2.m_code == ri.code) {
                return i;
            }
        }
        return -1;
    }

    int findThirdInputFrom(vector<RawInput> &listInputs) const {
        if(size != InputChordSize::_3) return -1;
        for(U32 i = 0 ; i<listInputs.size() ; ++i) {
            auto const& ri = listInputs[i];
            if(this->_3.m_source == ri.source &&
               this->_3.m_type == ri.type &&
               this->_3.m_code == ri.code) {
                return i;
            }
        }
        return -1;
    }
};

using InputCallbackType = function<void(RawInput ri, float frameDuration)>;

}

#endif //GANESHENGINE_GHINPUTUTILS_H
