#ifndef GANESHENGINE_GHGLRENDERERMANAGER_H
#define GANESHENGINE_GHGLRENDERERMANAGER_H

#include "ghHeaders.h"
#include "ghSystem.h"

#include "graphics/ghGLModel.h"

class GLFWwindow;

namespace ganeshEngine {

class RendererManager : public System<RendererManager> {
private:
    GLFWwindow* mpWindow;

public:
    void update();

protected:
    void vInitialize() override;
    void vDestroy() override;
};

extern RendererManager&(*gRenderer)();
}

#endif //GANESHENGINE_GHGLRENDERERMANAGER_H
