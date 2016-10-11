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

void RenderManager::draw() {
    for(IRenderObjectState* ros : mObjectStates) {
        mpRenderAPI->drawState(ros);
    }
}

void RenderManager::onComponentRegistered(Event* event) {
	ComponentRegisteredEvent* e = static_cast<ComponentRegisteredEvent*>(event);
    Component* c = e->getRegisteredComponent();

    if (c->getRTTI().isSame(ModelComponent::rtti)) {
        ModelComponent *mc = static_cast<ModelComponent*>(c);

        ResourceHandler<Mesh> hMesh = gResource().getResource<Mesh>(mc->getMeshStringId());
        if(hMesh == nullptr) {
            _WARNING("Unable to load the required Mesh to initialize the render state", LOG_CHANNEL::RENDER);
            return;
        }

        IRenderObjectState* ros = mpRenderAPI->loadPrimitive(hMesh.get()->getBuffer());
        mObjectStates.push_back(ros);
    }
    /*
    else if (c->getRTTI().isSame(LightComponent::rtti)) {
    }
    */
}

void RenderManager::onComponentUnregistered(Event* event) {}

RenderManager &(*gRender)() = &RenderManager::get;

}