#ifndef GANESHENGINE_RENDEROPENGLOBJECTSTATE_H
#define GANESHENGINE_RENDEROPENGLOBJECTSTATE_H

#include <render/ghIRenderObjectState.hpp>

namespace ganeshEngine {

class RenderOpenglObjectState : public IRenderObjectState {

public:
	GLuint mVBO;
	GLuint mVAO;

	//mesh id
	//Shader
};

}

#endif //GANESHENGINE_RENDEROPENGLOBJECTSTATE_H
