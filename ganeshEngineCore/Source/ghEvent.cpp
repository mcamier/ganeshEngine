#include <vector>

#include "ghEvent.h"

namespace ganeshEngine {

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

/*
 * EventManager
 */

EventManager::EventManager() {}

EventManager::~EventManager() {}

void EventManager::vInitialize() {}

void EventManager::vDestroy() {}

void EventManager::vUpdate(const Clock& clock) {
	Event *event;
	while (!m_EventQueue.empty()) {
		event = m_EventQueue.back();

		auto pair = m_Listeners.equal_range(event->getType());
		for (multimap<stringId, EventCallback>::iterator it = pair.first;
			 it != pair.second;
			 ++it) {
			(*it).second(event);
		}
		m_EventQueue.pop_back();
	}
}

void EventManager::fireEvent(Event *event) {
	auto pair = m_Listeners.equal_range(event->getType());
	for (multimap<stringId, EventCallback>::iterator it = pair.first;
		 it != pair.second;
		 ++it) {
		(*it).second(event);
	}
}

void EventManager::queueEvent(Event *event) {
	m_EventQueue.push_back(event);
}

void EventManager::addListener(stringId eventType, EventCallback callback) {
	m_Listeners.insert(pair<stringId, EventCallback>(eventType, callback));
}

void EventManager::removeAllListeners(stringId eventType) {
	m_Listeners.erase(m_Listeners.find(eventType));
}

EventManager &(*gEvent)() = &EventManager::get;

}