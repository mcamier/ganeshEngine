#ifndef GANESHENGINE_GHRENDERMANAGER_H
#define GANESHENGINE_GHRENDERMANAGER_H

#include "ghIRenderAPI.hpp"

namespace ganeshEngine {

/**
 * RenderManager is a statefull service responsible of drawing.
 * It holds an instance of RenderAPICore, the stateless layer of communication with the underlying graphical programming
 * interface
 */
class RenderManager {
protected:
	IRenderAPI *mpRenderAPI;

public:
	RenderManager(IRenderAPI *renderAPI) : mpRenderAPI(renderAPI) {}

	virtual void doAwesomeStuff() = 0;
};

}

#endif