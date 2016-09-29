#ifndef GANESHENGINE_RENDERGLAPI_H
#define GANESHENGINE_RENDERGLAPI_H

#include <render/ghIRenderAPI.hpp>

namespace ganeshEngine {

class RenderOpenglAPI : public IRenderAPI {
public:
	void vInitialize() override;
	void vDestroy() override;
};

}

#endif //GANESHENGINE_RENDERGLAPI_H
