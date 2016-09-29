#include <render/ghRenderManager.hpp>

namespace ganeshEngine {

RenderManager::RenderManager(IRenderAPI *renderAPI) : mpRenderAPI(renderAPI) {}

RenderManager::~RenderManager() {}

void RenderManager::vInitialize() {
	mpRenderAPI->vInitialize();
}

void RenderManager::vDestroy() {
	mpRenderAPI->vDestroy();
}

RenderManager &(*gRender)() = &RenderManager::get;

}