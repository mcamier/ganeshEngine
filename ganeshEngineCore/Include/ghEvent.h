#ifndef GHEVENT_H
#define GHEVENT_H

#include "ghHeaders.h"
#include "ghSystem.h"

namespace ganeshEngine {

using namespace std;



using EventType = U32;

/**
*/
class Event {

private:
    EventType m_type;

public:
    Event(EventType type) : m_type(type) {}

    virtual ~Event() {}

    const EventType getType() const {
        return m_type;
    }
};

class JoystickStateChangeEvent : public Event {
private:
    int m_joystickIndex;
    int m_joystickState;

public:
    JoystickStateChangeEvent(int index, int state) :
            Event(GH_HASH("__GH_EVENT_JOYSTICK_STATE_CHANGE")),
            m_joystickIndex(index),
            m_joystickState(state) {}

    virtual ~JoystickStateChangeEvent() {}

    int getJoystickIndex() const {
        return m_joystickIndex;
    }

    int getJoystickState() const {
        return m_joystickState;
    }
};

using EventCallback = function<void(Event *)>;

/**
*/
class EventManager : public System<EventManager> {
    friend class System<EventManager>;

private:
    /**
     */
    vector<Event *> m_EventQueue;

    /**
     */
    multimap<EventType, EventCallback> m_Listeners;

    EventManager();

    virtual ~EventManager();

protected:
    void vInitialize() override;

    void vDestroy() override;

public:
    EventManager(const EventManager &) = delete;

    EventManager &operator=(const EventManager &) = delete;

    /**
     *
     */
    void update();

    /**
     *
     * @param eventData
     * @return
     */
    void const fireEvent(Event *eventData);

    /**
     *
     * @param eventData
     */
    void queueEvent(Event *eventData);

    /**
     *
     * @param
     * @param
     * @return
     */
    void const addListener(EventType, EventCallback);

    /**
     *
     * @param
     * @return
     */
    void const removeAllListeners(EventType);
};

extern EventManager &(*gEvent)();

}

#endif /* GHEVENT_H */

