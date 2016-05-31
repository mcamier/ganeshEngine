#ifndef GANESHENGINE_GHGLRENDERERMANAGER_H
#define GANESHENGINE_GHGLRENDERERMANAGER_H

#include "ghHeaders.h"
#include "ghSystem.h"

class GLFWwindow;

namespace ganeshEngine {

class RendererManager : public System<RendererManager> {
private:
    GLFWwindow* mWpWindow;

public:
    void update();

protected:
    void vInitialize() override;
    void vDestroy() override;
};

extern RendererManager&(*gRenderer)();
}

#endif //GANESHENGINE_GHGLRENDERERMANAGER_H
