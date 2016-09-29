#ifndef GANESHENGINE_RENDERVULKANAPI_H
#define GANESHENGINE_RENDERVULKANAPI_H

#include <render/ghIRenderAPI.hpp>

namespace ganeshEngine {

class RenderVulkanAPI : public IRenderAPI {
public:
	void vInitialize() override;
	void vDestroy() override;
};

}

#endif //GANESHENGINE_RENDERVULKANAPI_H
