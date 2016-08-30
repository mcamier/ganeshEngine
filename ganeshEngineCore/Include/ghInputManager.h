#ifndef GANESHENGINE_GHINPUTMANAGER_H
#define GANESHENGINE_GHINPUTMANAGER_H

#include "ghHeaders.h"
#include "ghSystem.h"
#include "ghInputUtils.h"
#include "ghInputContext.h"
#include "ghInputConfiguration.h"
#include "ghEvent.h"

namespace ganeshEngine {

using namespace std;


class InputManager : public System<InputManager> {
	friend class System<InputManager>;

private:
	/** Configuration object used during the initialization step of the object
	 * Contains the game's inputContext filled with input chord and/or input matches
	 */
	InputManagerConfiguration m_config;

	/** List of the registered input contexts in the manager
	 * Multiple inputContext could be active at the same time
	 */
	map<U32, unique_ptr<InputContext>> m_inputContexts;

	/** Map of input corresponding actions in the game
	 * the key is the hash of the actual name of the input action, the value is
	 * function called when input action is triggered
	 */
	map<U32, InputCallbackType> m_inputCallbacks;

    /** Contains all inputs read from the system during the current frame
     * this vector is cleared at thje end of each frames
     */
    queue<RawInput> m_frameRawInputs;

    /** Contains postponed input that belongs to a chord
     * This list contains input for maybe several frame, the time needed to detecte a valid chord
     * or when input chord detection lifetime is over
	 */
    vector<RawInput> m_postponedRawInputs;

    /** Array used to store each keyboard buttons state
     * Only used to determine if button is held down (was pressed once but not yet
     * released)
     */
	//RawInput m_keyboardButtonsState[GH_KEYBOARD_KEY_COUNT];

    /** Array used to store each mouse buttons state
     * Only used to determine if button is held down (was pressed once but not yet
     * released)
     */
	//RawInput m_mouseButtonsState[GH_MOUSE_KEY_COUNT];

	/** Joystick object responsible of storing the joystick's state
	 */
	array<Joystick*, GH_MAX_JOYSTICK> m_joystick;


protected:
	void vInitialize() override;
	void vDestroy() override;


public:
	InputManager(InputManagerConfiguration config) : m_config(config) {
		m_postponedRawInputs = vector<RawInput>();
		m_frameRawInputs = queue<RawInput>();
		m_inputContexts = map<U32, unique_ptr<InputContext>>();
		m_inputCallbacks = map<U32, InputCallbackType>();
	}
	InputManager(const InputManager &) = delete;
	InputManager &operator=(const InputManager &) = delete;

	void activeContext(int id, bool active);

	void registerInputContext(unique_ptr<InputContext> inputContext);

	void registerInputCallback(U32 callbackHash, InputCallbackType callback);

	template<class T>
	void registerInputCallback(U32 callbackHash, T *object, void (T::*TMethod)(RawInput ri, float deltaTime)) {
		auto f = std::bind(TMethod, object, placeholders::_1, placeholders::_2);
		m_inputCallbacks.insert(make_pair(callbackHash, f));
	}

	void update(float frameDuration);

private:
	void triggerPlainInputAction(RawInput ri, float deltaTime);

	void onJoystickStateChange(Event* event);

	void setKeyboardState(int key, InputType type);

	void setMouseState(int button, InputType type);

	void updateStates(RawInput target[], int size);
};

/**
 * Global getter of reference to the InputManager
 * @return reference to the InputManager
 */
extern InputManager &(*gInput)();
}

#endif //GANESHENGINE_GHINPUTMANAGER_H
