#ifndef GHEVENT_H
#define GHEVENT_H

#include "ghHeaders.h"
#include "ghSystem.h"

namespace ganeshEngine {

using namespace std;

using EventType = U32;

/**
 * Basic Event class that all other event have to extends in order to be used by the
 * input Manager
 */
class Event {
private:
	EventType m_type;

public:
	Event(EventType type) : m_type(type) {}
	virtual ~Event();

	/**
	 * Getter on the event's type
	 *
	 * @return event's type
	 */
	const EventType getType() const;
};
using EventCallback = function<void(Event *)>;

class JoystickStateChangeEvent : public Event {
private:
	int m_joystickIndex;
	int m_joystickState;

public:
	JoystickStateChangeEvent(int index, int state) :
			Event(GH_HASH("__GH_EVENT_JOYSTICK_STATE_CHANGE")),
			m_joystickIndex(index),
			m_joystickState(state) {}

	virtual ~JoystickStateChangeEvent();

	int getJoystickIndex() const;

	int getJoystickState() const;
};

/**
 * EventManager si the system in charge of storing thrown events and calling correspondant event once each game loop
 */
class EventManager : public System<EventManager> {
	friend class System<EventManager>;
private:
	vector<Event *> m_EventQueue;

	multimap<EventType, EventCallback> m_Listeners;

protected:
	void vInitialize() override;
	void vDestroy() override;

public:
	EventManager(const EventManager &) = delete;
	EventManager &operator=(const EventManager &) = delete;

	/**
	 * Update read all events stored m_EventQueue and call related event's callback stored
	 * in m_Listeners
	 */
	void vUpdate(const Clock& clock) override;

	/**
	 * Executes immediately the callbacks registered for the given input
	 *
	 * @param eventData Pointer the base class Event
	 */
	void fireEvent(Event *eventData);

	/**
	 * Enqueue a event in order to be processed at the next EventManager update call
	 * @param eventData Pointer the base class Event
	 */
	void queueEvent(Event *eventData);

	/**
	 * Register a callback method to be called when event occurs
	 *
	 * @param eventType event type to match to trigger callback
	 * @param callback method to execute when event occurs
	 */
	void addListener(EventType eventType, EventCallback callback);

	/**
	 * Remove all listerners of a given type of event
	 * @param eventType type of event to find
	 */
	void removeAllListeners(EventType eventType);

	/**
	 * Register a callback method to be called when event occurs
	 * The callback method is a member function of an object
	 *
	 * @param eventType event type to match to trigger callback
	 * @param object instance of the object
	 * @param TMethod pointer to the member function to use as callback
	 */
	template<class T>
	void addListener(EventType eventType, T *object, void (T::*TMethod)(Event *)) {
		auto f = std::bind(TMethod, object, placeholders::_1);
		m_Listeners.insert(pair<EventType, EventCallback>(eventType, f));
	}

private:
	EventManager();
	virtual ~EventManager();
};

extern EventManager &(*gEvent)();

}

#endif /* GHEVENT_H */

