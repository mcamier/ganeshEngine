#ifndef GANESHENGINE_GHGLRENDERERMANAGER_H
#define GANESHENGINE_GHGLRENDERERMANAGER_H

#include "ghHeaders.h"
#include "ghSystem.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/ghGLModel.h"

class GLFWwindow;

namespace ganeshEngine {

using namespace std;

extern vector<tuple<GLenum, string>> gGLContextParams;



class RendererManager : public System<RendererManager> {
private:
    GLFWwindow* mpWindow;

public:
    void update();

protected:
    void vInitialize() override;
    void vDestroy() override;

private:
	void glfwErrorCallback(int error, const char *message);
};

void gGlfwErrorCallback(int error, const char *message);

extern RendererManager&(*gRenderer)();
}

#endif //GANESHENGINE_GHGLRENDERERMANAGER_H
