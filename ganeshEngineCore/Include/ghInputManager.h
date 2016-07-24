#ifndef GANESHENGINE_GHINPUTMANAGER_H
#define GANESHENGINE_GHINPUTMANAGER_H

#include "ghHeaders.h"
#include "ghSystem.h"
#include "ghInputUtils.h"
#include "ghInputContext.h"
#include "ghInputConfiguration.h"

namespace ganeshEngine {

using namespace std;

class InputManager : public System<InputManager> {
    friend class System<InputManager>;

private:
    /** Inputs read from the system
     */
    vector<rawInput> rawInputs;

    /** register input contexts
     */
    map<int, unique_ptr<InputContext>> inputContexts;

    /**
     * configuration purpose variables
     */
    bool m_bConfigurationOnInitialize = false;

    /**
     */
    unique_ptr<InputManagerConfiguration> m_config;

    /**
     */
    map<U32, function<void(void) >> m_inputCallbacks;

    /**
     */
    int m_keyState[GH_BUTTON_ARRAY_SIZE];

protected:
    void vInitialize() override;
    void vDestroy() override;

public:

    InputManager() :
    m_bConfigurationOnInitialize(false),
    m_config(nullptr)
    {
    }

    InputManager(unique_ptr<InputManagerConfiguration> config) :
    m_bConfigurationOnInitialize(true),
    m_config(move(config))
    {
    }

    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;


    void activeContext(int id, bool active);
    void registerInputContext(unique_ptr<InputContext> inputContext);
    void registerInputCallback(U32 callbackHash, function<void(void) > callback);
    void update();

private:
    void detectChords();
    void detectPlainInputs();
};

/**
 * Global getter of reference to the InputManager
 * @return reference to the InputManager
 */
extern InputManager&(*gInput)();
}

#endif //GANESHENGINE_GHINPUTMANAGER_H
