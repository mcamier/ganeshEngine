#ifndef GANESHENGINE_GHRENDERMANAGER_H
#define GANESHENGINE_GHRENDERMANAGER_H

#include "ghIRenderAPI.hpp"
#include <ghSystem.hpp>
#include <event/ghEvent.hpp>

namespace ganeshEngine {

/**
 * RenderManager is a statefull service responsible of drawing.
 * It holds an instance of RenderAPICore, the stateless layer of communication with the underlying graphical programming
 * interface
 */
class RenderManager : public System<RenderManager> {
	friend class System<RenderManager>;

protected:
	IRenderAPI *mpRenderAPI;

	vector<IRenderObjectState*> mObjectStates;

private:
	RenderManager(IRenderAPI *renderAPI);

public:
	~RenderManager();
	RenderManager(const RenderManager &) = delete;
	RenderManager &operator=(const RenderManager &) = delete;

	void vUpdate(const Clock& clock) override;



protected:
	void vInitialize() override;
	void vDestroy() override;

	void draw();

private:
	void onComponentRegistered(Event*);

	void onComponentUnregistered(Event*);

};

extern RenderManager &(*gRender)();

}

#endif
