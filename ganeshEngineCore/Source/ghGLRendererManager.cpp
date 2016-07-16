#include <ghGLRendererManager.h>

#include <time.h>
#include <ghPlatform.h>
#include "ghSceneObject.h"
#include "ghApplication.h"

namespace ganeshEngine {

void RendererManager::vInitialize() {}
void RendererManager::vDestroy() { }

void RendererManager::preRender() {
    timespec t;
    t.tv_sec = 0;
    t.tv_nsec = gRandr(15,20)*500000;
    //nanosleep(&t, nullptr);

    glClearColor(0.2, 0.2, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererManager::render(Scene &scene) {
    scene.render();
}

void RendererManager::postRender() {
    glfwSwapBuffers(gPlatform().getWindow());
}

RendererManager&(*gRenderer)() = &RendererManager::get;
}