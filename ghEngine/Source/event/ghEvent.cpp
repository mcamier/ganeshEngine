#include <event/ghEvent.hpp>
#include <ecs/ghComponent.hpp>

#include <vector>

namespace ganeshEngine {

stringId GH_EVENT_JOYSTICK_STATE_CHANGE = gInternString("__GH_EVENT_JOYSTICK_STATE_CHANGE");
stringId GH_EVENT_EXIT_GAME = gInternString("__GH_EVENT_EXIT_GAME");
stringId GH_EVENT_ACTOR_REGISTERED = gInternString("__GH_EVENT_ACTOR_REGISTERED");
stringId GH_EVENT_ACTOR_UNREGISTERED = gInternString("__GH_EVENT_ACTOR_UNREGISTERED");
stringId GH_EVENT_COMPONENT_REGISTERED = gInternString("__GH_EVENT_COMPONENT_REGISTERED");
stringId GH_EVENT_COMPONENT_UNREGISTERED = gInternString("__GH_EVENT_COMPONENT_UNREGISTERED");

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

Component* ComponentRegisteredEvent::getRegisteredComponent() {
	return mpComponent;
}

}