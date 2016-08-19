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
	/**
	 * Configuration object used during the initialization step of the object
	 * Contains the game's inputContext filled with input chord and/or input matches
	 */
	unique_ptr<InputManagerConfiguration> m_config;

	/**
	 * List of the registered input contexts in the manager
	 * Multiple inputContext could be active at the same time
	 */
	map<U32, unique_ptr<InputContext>> m_inputContexts;

	/**
	 * Map of input corresponding actions in the game
	 * the key is the hash of the actual name of the input action, the value is
	 * function called when input action is triggered
	 */
	map<U32, InputCallbackType> m_inputCallbacks;

    /**
     * Contains all inputs read from the system during the actual frame
     * this vector is cleared atthje end of each frames
     */
    queue<rawInput> m_frameRawInputs;

    /**
	 * Contains postponed input that belongs to a chord
     * This list contains input for maybe several frame, the time needed to detecte a valid chord
     * or when input chord detection lifetime is over
	 */
    vector<rawInput> m_postponedRawInputs;

    /**
     * Array used to store each keyboard buttons state
     * Only used to determine if button is held down (was pressed once but not yet
     * released)
     */
	rawInput m_keyboardButtonsState[GH_BUTTON_ARRAY_SIZE];

    /**
     * Array used to store each mouse buttons state
     * Only used to determine if button is held down (was pressed once but not yet
     * released)
     */
	rawInput m_mouseButtonsState[GH_BUTTON_MOUSE_SIZE];

	/**
	 * Joystick object responsible of storing the joystick's state
	 */
	array<Joystick*, GH_MAX_JOYSTICK> m_joystick;

	/**
	 *
	 */
	U32 m_rawInputLifetimeChordDetection = 0;

protected:
	void vInitialize() override;
	void vDestroy() override;

public:
	InputManager() : m_config(nullptr) {}
	InputManager(unique_ptr<InputManagerConfiguration> config) : m_config(move(config)) {}
	InputManager(const InputManager &) = delete;
	InputManager &operator=(const InputManager &) = delete;

	/**
	 *
	 * @param id
	 * @param active
	 */
	void activeContext(int id, bool active);

	/**
	 *
	 * @param inputContext
	 */
	void registerInputContext(unique_ptr<InputContext> inputContext);

	/**
	 */
	void registerInputCallback(U32 callbackHash, InputCallbackType callback);

	/**
	 *
	 */
	void update(U32 frameDuration);

private:
	void triggerPlainInputAction(rawInput ri, U32 deltaTime);

	void onJoystickStateChange(Event* event);

	void setKeyboardState(int key, RawInput::TYPE type);

	void setMouseState(int button, RawInput::TYPE type);

	void updateStates(rawInput target[], int size);
};

/**
 * Global getter of reference to the InputManager
 * @return reference to the InputManager
 */
extern InputManager &(*gInput)();
}

#endif //GANESHENGINE_GHINPUTMANAGER_H
