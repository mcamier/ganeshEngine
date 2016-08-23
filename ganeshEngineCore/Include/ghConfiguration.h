#ifndef GANESHENGINE_GHCONFIGURATION_H
#define GANESHENGINE_GHCONFIGURATION_H

#include "ghHeaders.h"
#include "ghILogger.h"
#include "ghScene.h"
#include "ghResourceLoader.h"

namespace ganeshEngine {

using namespace std;

class Configuration {
public:
	string inputConfigurationFilename;
	string resourceConfigurationFilename;
	map<U32, ResourceLoader*> customResourceLoaders;
	vector<ILogger*> loggers;
	Scene* startScene;
};

}

#endif //GANESHENGINE_GHCONFIGURATION_H
