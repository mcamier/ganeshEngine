#include <ghGLRendererManager.h>


#include <time.h>
#include "ghSceneObject.h"
#include "ghApplication.h"

namespace ganeshEngine {

vector<tuple<GLenum, string>> gGLContextParams = {
    make_tuple<GLenum, string>(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS"),
    make_tuple<GLenum, string>(GL_MAX_CUBE_MAP_TEXTURE_SIZE, "GL_MAX_CUBE_MAP_TEXTURE_SIZE"),
    make_tuple<GLenum, string>(GL_MAX_DRAW_BUFFERS, "GL_MAX_DRAW_BUFFERS"),
    make_tuple<GLenum, string>(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS"),
    make_tuple<GLenum, string>(GL_MAX_TEXTURE_IMAGE_UNITS, "GL_MAX_TEXTURE_IMAGE_UNITS"),
    make_tuple<GLenum, string>(GL_MAX_TEXTURE_SIZE, "GL_MAX_TEXTURE_SIZE"),
    make_tuple<GLenum, string>(GL_MAX_VARYING_FLOATS, "GL_MAX_VARYING_FLOATS"),
    make_tuple<GLenum, string>(GL_MAX_VERTEX_ATTRIBS, "GL_MAX_VERTEX_ATTRIBS"),
    make_tuple<GLenum, string>(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS"),
    make_tuple<GLenum, string>(GL_MAX_VERTEX_UNIFORM_COMPONENTS, "GL_MAX_VERTEX_UNIFORM_COMPONENTS")
};

void RendererManager::vInitialize() {
    if( glfwInit() ) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        mpWindow = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
        glfwSetErrorCallback(gGlfwErrorCallback);

        if( mpWindow ) {
            glfwMakeContextCurrent(mpWindow);
            glewExperimental = GL_TRUE;
            GLuint err = glewInit();
            if(err == GLEW_OK) {
                glEnable(GL_DEPTH_TEST);
                glDepthFunc(GL_LESS);
                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);
                glFrontFace(GL_CW);

                const GLubyte *renderer = glGetString(GL_RENDERER);
                const GLubyte *version = glGetString(GL_VERSION);
                _INFO("RendererManager init : ");
                _INFO("\t renderer : " << renderer);
                _INFO("\t version : " << version);

                _INFO("GL Context param :");
                for(tuple<GLenum, string> param : gGLContextParams) {
                    int value = 0;
                    glGetIntegerv(std::get<0>(param), &value);
                    _INFO("\t" << std::get<1>(param) << " : " << value);
                }
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


void RendererManager::preRender() {
    timespec t;
    t.tv_sec = 0;
    t.tv_nsec = gRandr(15,20)*500000;
    nanosleep(&t, nullptr);

    glClearColor(0.2, 0.2, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererManager::render(Scene &scene) {
    scene.render();
}

void RendererManager::postRender() {
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

void gGlfwErrorCallback(int error, const char *message) {
    _ERROR("GLFW ERROR : code " << error << " message : ");
}

RendererManager&(*gRenderer)() = &RendererManager::get;
}