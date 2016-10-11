#ifndef GHEVENT_H
#define GHEVENT_H

#include <util/ghStringId.hpp>
#include <ghSystem.hpp>

namespace ganeshEngine {

class Component;

using namespace std;

extern stringId GH_EVENT_JOYSTICK_STATE_CHANGE;
extern stringId GH_EVENT_EXIT_GAME;
extern stringId GH_EVENT_ACTOR_REGISTERED;
extern stringId GH_EVENT_ACTOR_UNREGISTERED;
extern stringId GH_EVENT_COMPONENT_REGISTERED;
extern stringId GH_EVENT_COMPONENT_UNREGISTERED;

/**
 * Basic Event class that all other event have to extends in order to be used by the
 * input Manager
 */
class Event {
private:
	stringId mType;

public:
	Event(stringId type) : mType(type) {}
	virtual ~Event();

	/**
	 * Getter on the event's type
	 *
	 * @return event's type
	 */
	const stringId getType() const;
};

using EventCallback = function<void(Event *)>;


class JoystickStateChangeEvent : public Event {
private:
	int m_joystickIndex;
	int m_joystickState;

public:
	JoystickStateChangeEvent(int index, int state) :
			Event(GH_EVENT_JOYSTICK_STATE_CHANGE),
			m_joystickIndex(index),
			m_joystickState(state) {}

	virtual ~JoystickStateChangeEvent();

	int getJoystickIndex() const;

	int getJoystickState() const;
};

class ActorRegisteredEvent : public Event {
public:
	ActorRegisteredEvent() :
			Event(GH_EVENT_ACTOR_REGISTERED) {}
};


class ActorUnregisteredEvent : public Event {
public:
	ActorUnregisteredEvent() :
			Event(GH_EVENT_ACTOR_UNREGISTERED) {}
};


class ComponentRegisteredEvent : public Event {
private:
	Component* mpComponent;

public:
	ComponentRegisteredEvent(Component* component) :
			Event(GH_EVENT_COMPONENT_REGISTERED),
			mpComponent(component) {}

	Component* getRegisteredComponent();
};


class ComponentUnregisteredEvent : public Event {
public:
	ComponentUnregisteredEvent() :
			Event(GH_EVENT_COMPONENT_UNREGISTERED) {}
};

}

#endif /* GHEVENT_H */

