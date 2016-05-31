#include <iostream>
#include "ghCore.h"
#include "ghApplication.h"
#include "graphics/ghFrustum.h"

using namespace std;
using namespace ganeshEngine;


int main() {
	Application::Initialize();
    /** After application initialization all singletons used by the engine
     *  are created and initialized, so all engine's customization, plugins
     *  addition should take place here, before the start of the main loop
     */
    //Application::RunLoop();
	Frustum f = Frustum(16.0f/9.0f, 80, 1.0f, 1000.0f);

dew    Application::Destroy();
    return 0;
}