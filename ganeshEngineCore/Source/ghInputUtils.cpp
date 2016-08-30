#include "ghInputUtils.h"

namespace ganeshEngine {

namespace inputDetails {

template<>
const char *toString<InputSource>(InputSource value) {
	/*if (value == InputSource::MOUSE) return inputDetails::sourceMouse;
	if (value == InputSource::KEYBOARD) return inputDetails::sourceKeyboard;
	if (value == InputSource::DEVICE) return inputDetails::sourceDevice;*/
}

template<>
const char *toString<InputType>(InputType value) {
	/*if (value == InputType::BUTTON_UP) return inputDetails::typeUp;
	if (value == InputType::BUTTON_PRESS) return inputDetails::typePress;
	if (value == InputType::BUTTON_DOWN) return inputDetails::typeDown;
	if (value == InputType::BUTTON_RELEASE) return inputDetails::typeRelease;
	if (value == InputType::AXIS) return inputDetails::typeAxis;*/
}

template<>
const char *toString<InputCode>(InputCode value) {
	/*if (value == InputCode::MOUSE_LEFT)return keyMouseLeft;
	if (value == InputCode::MOUSE_RIGHT)return keyMouseRight;*/
	//TODO reimplement others
}

template<>
InputSource fromString<InputSource>(const char *value) {
	/*if (strcmp(value, inputDetails::sourceMouse) == 0) return InputSource::MOUSE;
	if (strcmp(value, inputDetails::sourceKeyboard) == 0) return InputSource::KEYBOARD;
	if (strcmp(value, inputDetails::sourceDevice) == 0) return InputSource::DEVICE;*/
}

template<>
InputType fromString<InputType>(const char *value) {
	/*if (strcmp(value, inputDetails::typeUp) == 0) return InputType::BUTTON_UP;
	if (strcmp(value, inputDetails::typePress) == 0) return InputType::BUTTON_PRESS;
	if (strcmp(value, inputDetails::typeDown) == 0) return InputType::BUTTON_DOWN;
	if (strcmp(value, inputDetails::typeRelease) == 0) return InputType::BUTTON_RELEASE;
	if (strcmp(value, inputDetails::typeAxis) == 0) return InputType::AXIS;*/
}

template<>
InputCode fromString<InputCode>(const char *value) {
/*	if (strcmp(value, inputDetails::keyMouseLeft) == 0) return InputCode::MOUSE_LEFT;
	if (strcmp(value, inputDetails::keyMouseRight) == 0) return InputCode::MOUSE_RIGHT;*/
	//TODO reimplement others
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

}