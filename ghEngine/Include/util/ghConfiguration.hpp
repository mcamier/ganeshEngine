#ifndef GANESHENGINE_GHCONFIGURATION_H
#define GANESHENGINE_GHCONFIGURATION_H


#include <util/ghILogger.hpp>
#include "../resource/ghResourceLoader.hpp"

namespace ganeshEngine {

using namespace std;

class Configuration {
public:
	string inputConfigurationFilename;
	string resourceConfigurationFilename;
	map<U32, ResourceLoader*> customResourceLoaders;
	vector<ILogger*> loggers;
};

}

#endif //GANESHENGINE_GHCONFIGURATION_H
