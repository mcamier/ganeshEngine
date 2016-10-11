#ifndef GANESHENGINE_RENDERVULKANAPI_H
#define GANESHENGINE_RENDERVULKANAPI_H

#include <render/ghIRenderAPI.hpp>
#include <render/ghIRenderObjectState.hpp>

namespace ganeshEngine {

class RenderVulkanAPI : public IRenderAPI {
public:
	void vInitialize() override;
	void vDestroy() override;

	IRenderObjectState* loadPrimitive(std::vector<float>* vertexBuffer) override;

	void drawState(IRenderObjectState* state) override;
};

}

#endif //GANESHENGINE_RENDERVULKANAPI_H
