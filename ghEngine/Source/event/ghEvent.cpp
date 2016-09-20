#include <event/ghEvent.hpp>

#include <vector>

namespace ganeshEngine {

stringId GH_EVENT_JOYSTICK_STATE_CHANGE = gInternString("__GH_EVENT_JOYSTICK_STATE_CHANGE");
stringId GH_EVENT_EXIT_GAME = gInternString("__GH_EVENT_EXIT_GAME");

/*
 * Event
 */
Event::~Event() {}

const stringId Event::getType() const {
	return mType;
}

/*
 * JoystickStateChangeEvent
 */
JoystickStateChangeEvent::~JoystickStateChangeEvent() {}

int JoystickStateChangeEvent::getJoystickIndex() const {
	return m_joystickIndex;
}

int JoystickStateChangeEvent::getJoystickState() const {
	return m_joystickState;
}

}