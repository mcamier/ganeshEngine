#ifndef GANESHENGINE_GHGLRENDERERMANAGER_H
#define GANESHENGINE_GHGLRENDERERMANAGER_H

#include "ghHeaders.h"
#include "ghSystem.h"
#include "ghScene.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ghModel.h"

class GLFWwindow;

namespace ganeshEngine {

    using namespace std;

/**
 *
 */
    extern vector<tuple<GLenum, string>> gGLContextParams;


    class RendererManager : public System<RendererManager> {
        friend class System<RendererManager>;

    private:
        RendererManager() {}

    public:
        RendererManager(const RendererManager &) = delete;

        RendererManager &operator=(const RendererManager &) = delete;

        ~RendererManager() {}

        void preRender();

        void render(Scene *scene);

        void postRender();

    protected:
        /**
         * Initialization of GLFW and GLEW, creation of the windows and settings
         * default rendering parameters
         */
        void vInitialize() override;

        /**
         * Free everything used by GLFW and GLEW
         */
        void vDestroy() override;
    };

/**
 * Global getter of reference to the RendererManager
 * @return reference to the RendererManager
 */
    extern RendererManager &(*gRenderer)();
}

#endif //GANESHENGINE_GHGLRENDERERMANAGER_H
