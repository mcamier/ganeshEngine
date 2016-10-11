#ifndef GANESHENGINE_RENDERGLAPI_H
#define GANESHENGINE_RENDERGLAPI_H

#include <render/ghIRenderAPI.hpp>

namespace ganeshEngine {

class RenderOpenglAPI : public IRenderAPI {
public:
	void vInitialize() override;
	void vDestroy() override;

	IRenderObjectState* loadPrimitive(std::vector<float>* vertexBuffer) override;

	void drawState(IRenderObjectState* state) override;
};

}

#endif //GANESHENGINE_RENDERGLAPI_H
