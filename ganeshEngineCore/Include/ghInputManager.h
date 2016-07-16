#ifndef GANESHENGINE_GHINPUTMANAGER_H
#define GANESHENGINE_GHINPUTMANAGER_H

#include "ghHeaders.h"
#include "ghSystem.h"
#include "ghInputUtils.h"
#include "ghInputContext.h"

#include <vector>
#include <map>
#include <memory>

namespace ganeshEngine{

using namespace std;

class InputManager : public System<InputManager> {
    friend class System<InputManager>;

private:
    vector<rawInput> rawInputs;
    map<int, unique_ptr<InputContext>> inputContexts;

protected:
    void vInitialize() override;
    void vDestroy() override;

public:
    void activeContext(int id, bool active);
    void submitInput(rawInput input);
    void registerInputContext(unique_ptr<InputContext> inputContext);
    void update();
};

/**
 * Global getter of reference to the InputManager
 * @return reference to the InputManager
 */
extern InputManager&(*gInput)();

}



#endif //GANESHENGINE_GHINPUTMANAGER_H
