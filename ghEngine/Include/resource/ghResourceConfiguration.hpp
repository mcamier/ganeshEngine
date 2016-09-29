#ifndef GANESHENGINE_GHRESOURCECONFIGURATION_H
#define GANESHENGINE_GHRESOURCECONFIGURATION_H


#include "ghResourceUtil.hpp"

#include "rapidjson/document.h"
#include <cstdio>
#include <cstring>
#include <vector>
#include <memory>

namespace ganeshEngine {

using namespace std;
using namespace rapidjson;

/**
 *
 */
class ResourceConfiguration {
private:
    vector<resourceEntry> m_resources;

    ResourceConfiguration();

public:
    virtual ~ResourceConfiguration();

    static ResourceConfiguration* loadFromFile(string configFilename);

    vector<resourceEntry> &getResourceEntries();

private:
    static void readResources(const Value &node, ResourceConfiguration *conf);

    static void readResource(const Value &node, ResourceConfiguration *conf);
};

}
#endif //GANESHENGINE_GHRESOURCECONFIGURATION_H
