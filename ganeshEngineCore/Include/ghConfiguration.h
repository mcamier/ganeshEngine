#ifndef GANESHENGINE_GHCONFIGURATION_H
#define GANESHENGINE_GHCONFIGURATION_H

#include "ghHeaders.h"
#include "ghILogger.h"
#include "ghScene.h"

namespace ganeshEngine {

using namespace std;

class Configuration {
public:
	string inputConfigurationFilename;
	string resourceConfigurationFilename;
	vector<ILogger*> loggers;
	Scene* startScene;
};

}

#endif //GANESHENGINE_GHCONFIGURATION_H
