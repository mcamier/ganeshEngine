#include <ghGLRendererManager.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include "ghApplication.h"

namespace ganeshEngine {

void RendererManager::vInitialize() {
    if( glfwInit() ) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        mpWindow = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);

        if( mpWindow ) {
            glfwMakeContextCurrent(mpWindow);
            glewExperimental = GL_TRUE;
            GLuint err = glewInit();
            if(err == GLEW_OK) {
                glEnable(GL_DEPTH_TEST);
                glDepthFunc(GL_LESS);

                const GLubyte *renderer = glGetString(GL_RENDERER);
                const GLubyte *version = glGetString(GL_VERSION);
                _TRACE("RendererManager init : ");
                _TRACE("\t renderer : " << renderer);
                _TRACE("\t version : " << version);

            } else {
                _FATAL("failed to initialize GLEW");
            }
        } else {
            _FATAL("ERROR ON WINDOW CREATION");
        }
    } else {
        _FATAL("ERROR ON GLFW INIT");
    }



}

void RendererManager::update() {
    timespec t;
    t.tv_sec = 0;
    t.tv_nsec = gRandr(15,20)*500000;
    nanosleep(&t, nullptr);

    glClearColor(0.2, 0.2, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwSwapBuffers(mpWindow);

    /* TODO this statements have to be relocated outside of the RendererManager*/
    glfwPollEvents();
    if(GLFW_PRESS == glfwGetKey(mpWindow, GLFW_KEY_ESCAPE)) {
        gApp().shutdown();
    }
}

void RendererManager::vDestroy() {
    glfwTerminate();
}

RendererManager&(*gRenderer)() = &RendererManager::get;
}