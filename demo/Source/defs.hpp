#ifndef GANESHENGINE_DEFS_HPP
#define GANESHENGINE_DEFS_HPP

#include <util/ghStringId.hpp>

namespace ganeshEngine {

static stringId GH_DEMO_ACTION_MOVE_UP = gInternString("demoMatchMoveUp");
static stringId GH_DEMO_ACTION_MOVE_DOWN = gInternString("demoMatchMoveDown");
static stringId GH_DEMO_ACTION_MOVE_RIGHT = gInternString("demoMatchMoveRight");
static stringId GH_DEMO_ACTION_MOVE_LEFT = gInternString("demoMatchMoveLeft");
static stringId GH_DEMO_ACTION_RESET = gInternString("demoMatchReset");

static stringId teapotMeshStringId = gInternString("teapot");
static stringId demoResourceShaderP = gInternString("defaultShaderProgram");
static stringId demoResourceShaderV = gInternString("defaultVertexShader");
static stringId demoResourceShaderF = gInternString("defaultFragmentShader");

}

#endif //GANESHENGINE_DEFS_HPP
