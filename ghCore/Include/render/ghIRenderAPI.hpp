#ifndef GANESHENGINE_GHIRENDERAPI_H
#define GANESHENGINE_GHIRENDERAPI_H

#include <vector>
#include "ghIRenderObjectState.hpp"

namespace ganeshEngine {

class IRenderAPI {
public:
	virtual void vInitialize() = 0;
	virtual void vDestroy() = 0;

	/**
	 * Load into the graphic card memory a given vertex buffer.
	 * <p>
	 * The expected memory pattern is : vx, vy, vz, vn_x, vn_y, vn_z for each vertex, then 3 contiguous vertices gives
	 * a face.
	 *
	 * @param vertexBuffer
	 */
	virtual IRenderObjectState* loadPrimitive(std::vector<float>* vertexBuffer) = 0;

	/**
	 * Draw a single occurence of object
	 * @param state
	 */
	virtual void drawState(IRenderObjectState* state) = 0;
};

}

#endif //GANESHENGINE_GHRENDERAPICORE_H
