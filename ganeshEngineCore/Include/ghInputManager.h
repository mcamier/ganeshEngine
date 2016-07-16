#ifndef GANESHENGINE_GHINPUTMANAGER_H
#define GANESHENGINE_GHINPUTMANAGER_H

#include "ghHeaders.h"
#include "ghSystem.h"
#include "ghInputUtils.h"

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ganeshEngine{

using namespace std;

class InputManager : public System<InputManager> {
    friend class System<InputManager>;

private:
    vector<rawInput> rawInputs;

protected:
    void vInitialize() override;
    void vDestroy() override;

public:
    void registerInput(rawInput input);
    void update();
};

/**
 * Global getter of reference to the InputManager
 * @return reference to the InputManager
 */
extern InputManager&(*gInput)();

}



#endif //GANESHENGINE_GHINPUTMANAGER_H
