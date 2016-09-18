#include <ghGLRendererManager.h>

#include <time.h>
#include <ghPlatform.h>
#include "ghApplication.h"

namespace ganeshEngine {

    void RendererManager::vInitialize() {}

    void RendererManager::vDestroy() {}

    void RendererManager::preRender() {
        glClearColor(0.2, 0.2, 0.2, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RendererManager::render(Scene *scene) {
        //scene->render();
    }

    void RendererManager::postRender() {
        glfwSwapBuffers(gPlatform().getWindow());
    }

    RendererManager &(*gRenderer)() = &RendererManager::get;
}