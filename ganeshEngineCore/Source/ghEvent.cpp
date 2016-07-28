#include <vector>

#include "ghEvent.h"

namespace ganeshEngine {

    EventManager::EventManager() {
    }

    EventManager::~EventManager() {
    }

    void EventManager::vInitialize() {
    }

    void EventManager::vDestroy() {
    }

    void EventManager::update() {
        Event *event;
        while (!m_EventQueue.empty()) {
            event = m_EventQueue.back();

            auto pair = m_Listeners.equal_range(event->getType());
            for (multimap<EventType, EventCallback>::iterator it = pair.first;
                 it != pair.second;
                 ++it) {
                (*it).second(event);
            }
            m_EventQueue.pop_back();
        }
    }

    void EventManager::fireEvent(Event *event) {
        auto pair = m_Listeners.equal_range(event->getType());
        for (multimap<EventType, EventCallback>::iterator it = pair.first;
             it != pair.second;
             ++it) {
            (*it).second(event);
        }
    }

    void EventManager::queueEvent(Event *event) {
        m_EventQueue.push_back(event);
    }

    void EventManager::addListener(EventType eventType, EventCallback callback) {
        m_Listeners.insert(pair<EventType, EventCallback>(eventType, callback));
    }

    void EventManager::removeAllListeners(EventType eventType) {
        m_Listeners.erase(m_Listeners.find(eventType));
    }

    EventManager &(*gEvent)() = &EventManager::get;

}