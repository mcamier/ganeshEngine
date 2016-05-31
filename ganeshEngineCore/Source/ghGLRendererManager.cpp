#include <ghGLRendererManager.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>

namespace ganeshEngine {

    void RendererManager::vInitialize() {
        if( !glfwInit() ) {
            fprintf(stderr, "ERROR ON GLFW INIT");
        }

        mWpWindow = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
        if( !mWpWindow ) {
            fprintf(stderr, "ERROR ON WINDOW CREATION");
            glfwTerminate();
        }

        glfwMakeContextCurrent(mWpWindow);
        glewExperimental = GL_TRUE;
        GLuint err = glewInit();
        if(err != GLEW_OK) {
            std::cerr << "failed to initialize GLEW"<< std::endl;
            exit(1);
        }
	    if (!GLEW_VERSION_2_1) {
		    std::cerr << "GLEW 2.1 not supported" << std::endl;
		    exit(1);
	    }
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        const GLubyte *renderer = glGetString(GL_RENDERER);
        const GLubyte *version = glGetString(GL_VERSION);
        std::cout << "RendererManager init : " << std::endl;
        std::cout << "\t renderer : " << renderer << std::endl;
        std::cout << "\t version : " << version << std::endl;
    }

    void RendererManager::update() {
        timespec t;
        t.tv_sec = 0;
        t.tv_nsec = gRandr(15,20)*1000000;
        nanosleep(&t, nullptr);
        glfwSwapBuffers(mWpWindow);
    }

    void RendererManager::vDestroy() {
        glfwTerminate();
    }

    RendererManager&(*gRenderer)() = &RendererManager::get;
}