#ifndef GANESHENGINE_GHIRENDERAPI_H
#define GANESHENGINE_GHIRENDERAPI_H

namespace ganeshEngine {

class IRenderAPI {
public:
	virtual void vInitialize() = 0;
	virtual void vDestroy() = 0;
};

}

#endif //GANESHENGINE_GHRENDERAPICORE_H
