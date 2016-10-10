#include <render/ghRenderManager.hpp>
#include <event/ghEventManager.hpp>
#include <util/ghILogger.hpp>
#include <util/ghRTTI.hpp>
#include <ecs/ghModelComponent.hpp>
#include <ecs/ghComponent.hpp>

namespace ganeshEngine {

RenderManager::RenderManager(IRenderAPI *renderAPI) : mpRenderAPI(renderAPI) {}

RenderManager::~RenderManager() {}

void RenderManager::vInitialize() {
	mpRenderAPI->vInitialize();

	gEvent().addListener(GH_EVENT_COMPONENT_REGISTERED, this, &RenderManager::onComponentRegistered);
	gEvent().addListener(GH_EVENT_COMPONENT_UNREGISTERED, this, &RenderManager::onComponentUnregistered);
}

void RenderManager::vDestroy() {
	mpRenderAPI->vDestroy();
}

void RenderManager::vUpdate(const Clock& clock) {

}

void RenderManager::onComponentRegistered(Event* event) {
	ComponentRegisteredEvent* e = static_cast<ComponentRegisteredEvent*>(event);
}

void RenderManager::onComponentUnregistered(Event* event) {
	ComponentUnregisteredEvent* e = static_cast<ComponentUnregisteredEvent*>(event);
}

RenderManager &(*gRender)() = &RenderManager::get;

}