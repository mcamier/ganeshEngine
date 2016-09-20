#ifndef GANESHENGINE_GHINPUTMANAGER_H
#define GANESHENGINE_GHINPUTMANAGER_H

#include "ghHeaders.h"
#include "ghSystem.h"
#include "ghInputUtils.h"
#include "ghInputContext.h"
#include "ghInputConfiguration.h"
#include "ghEvent.h"
#include "ghClock.h"

namespace ganeshEngine {

using namespace std;

class InputManager : public System<InputManager> {
	friend class System<InputManager>;

private:
	/** Configuration object used during the initialization step of the object
	 * Contains the game's inputContext filled with input chord and/or input matches
	 */
	InputManagerConfiguration mInputConfig;

	/** List of the registered input contexts in the manager
	 * Multiple inputContext could be active at the same time
	 */
	map<stringId, unique_ptr<InputContext>> mInputContexts;

	/** Map of input corresponding actions in the game
	 * the key is the hash of the actual name of the input action, the value is
	 * function called when input action is triggered
	 */
	map<stringId, InputCallbackType> mInputCallbacks;

    /** Contains all inputs read from the system during the current frame
     * this vector is cleared at thje end of each frames
     */
    queue<RawInput> mFrameRawInputs;

    /** Contains postponed input that belongs to a chord
     * This list contains input for maybe several frame, the time needed to detecte a valid chord
     * or when input chord detection lifetime is over
	 */
    vector<RawInput> mPostponedRawInputs;

	map<InputCode, RawInput> mHeldButtonRawInputs;

	array<Joystick, GH_MAX_JOYSTICK+1> mJoysticks;

protected:
	void vInitialize() override;
	void vDestroy() override;

public:
	InputManager(InputManagerConfiguration config) : mInputConfig(config) {
		mPostponedRawInputs = vector<RawInput>();
		mFrameRawInputs = queue<RawInput>();
		mInputContexts = map<stringId, unique_ptr<InputContext>>();
		mInputCallbacks = map<stringId, InputCallbackType>();
		mJoysticks = array<Joystick, GH_MAX_JOYSTICK+1>();
		mHeldButtonRawInputs = map<InputCode, RawInput>();
	}
	InputManager(const InputManager &) = delete;
	InputManager &operator=(const InputManager &) = delete;

	void activeContext(stringId id, bool active);

	void registerInput(RawInput rawInput);

	void registerInputContext(unique_ptr<InputContext> inputContext);

	void registerInputCallback(stringId callbackHash, InputCallbackType callback);

	template<class T>
	void registerInputCallback(stringId callbackHash, T *object, void (T::*TMethod)(RawInput ri, float deltaTime)) {
		auto f = std::bind(TMethod, object, placeholders::_1, placeholders::_2);
		mInputCallbacks.insert(make_pair(callbackHash, f));
	}

	void vUpdate(const Clock& frameDuration);

private:
	void triggerPlainInputAction(RawInput ri, float deltaTime);

	void onJoystickStateChange(Event* event);

	void initCallbacks();

	void initDefaultInputContext();
};

/**
 * Global getter of reference to the InputManager
 * @return reference to the InputManager
 */
extern InputManager &(*gInput)();
}

#endif //GANESHENGINE_GHINPUTMANAGER_H
