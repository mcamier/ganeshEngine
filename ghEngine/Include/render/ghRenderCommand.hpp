#ifndef GANESHENGINE_GHRENDERCOMMAND_H
#define GANESHENGINE_GHRENDERCOMMAND_H

#include "util/ghRTTI.hpp"
#include "ghRenderTypes.hpp"

namespace ganeshEngine {

/**
 * Describes one rendering instruction which could be sent to the RendererManager
 */
class RenderCommand {

RTTI_DECL()

private:
	bool mbDebugPurpose;
	RenderType mRenderType;

public:
	RenderCommand(bool debugPurpose, RenderType renderType);

	virtual ~RenderCommand();
};

}

#endif //GANESHENGINE_GHRENDERCOMMAND_H
