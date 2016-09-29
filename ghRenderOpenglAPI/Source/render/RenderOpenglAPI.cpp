#include <render/RenderOpenglAPI.hpp>
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GL/gl.h>
#include <util/ghILogger.hpp>
#include <sstream>
#include <tuple>
#include <vector>

namespace ganeshEngine {

using namespace std;

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

void RenderOpenglAPI::vInitialize() {
	GLuint err = glewInit();
	if (err == GLEW_OK) {
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

		const GLubyte *renderer = glGetString(GL_RENDERER);
		const GLubyte *version = glGetString(GL_VERSION);
		_DEBUG("RendererManager init : ", LOG_CHANNEL::DEFAULT);
		_DEBUG("\t renderer : " << renderer, LOG_CHANNEL::DEFAULT);
		_DEBUG("\t version : " << version, LOG_CHANNEL::DEFAULT);

		_DEBUG("GL Context param :", LOG_CHANNEL::DEFAULT);
		for (std::tuple<GLenum, std::string> param : gGLContextParams) {
			int value = 0;
			glGetIntegerv(std::get<0>(param), &value);
			_DEBUG("\t" << std::get<1>(param) << " : " << value, LOG_CHANNEL::DEFAULT);
		}
	} else {
		_ERROR("failed to initialize GLEW", LOG_CHANNEL::DEFAULT);
	}
}

void RenderOpenglAPI::vDestroy() {
}

}