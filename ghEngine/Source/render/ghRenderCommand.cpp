#include "render/ghRenderCommand.hpp"

namespace ganeshEngine {

RTTI_IMPL_BASE(RenderCommand)

RenderCommand::RenderCommand(bool debugPurpose, RenderType renderType) :
	mbDebugPurpose(debugPurpose) ,
	mRenderType(renderType) {}

RenderCommand::~RenderCommand() {}

}