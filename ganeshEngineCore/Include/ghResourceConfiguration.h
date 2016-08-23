#ifndef GANESHENGINE_GHRESOURCECONFIGURATION_H
#define GANESHENGINE_GHRESOURCECONFIGURATION_H

#include "ghHeaders.h"

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>

namespace ganeshEngine {

using namespace std;
using namespace rapidjson;

typedef struct resourceMetadata_s {
    string name;
    string value;
} resourceMetadata;

typedef struct resourceEntry_s {
    string name;
    string filename;
    string importerName;
    map<U32, resourceMetadata> metadatas;
} resourceEntry;

enum class ResourceLocationType {
    FOLDER,
    ARCHIVE
};

/**
 *
 */
class ResourceConfiguration {
private:
    ResourceLocationType m_resourceLocationType;
    string m_resourceLocation;
    vector<resourceEntry> m_resources;

    ResourceConfiguration() {}

public:
    virtual ~ResourceConfiguration() {}

    static unique_ptr<ResourceConfiguration> loadFromFile(string configFilename) {
        _DEBUG("Load Resource Configuration : " << configFilename, LOG_CHANNEL::INPUT);
        ResourceConfiguration *conf = new ResourceConfiguration();
        Document jsonConfig;
        char readBuffer[65536];

        FILE *fp = fopen(configFilename.c_str(), "rb");
        FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        jsonConfig.ParseStream(is);

        ResourceLocationType resourceLocationType;
        string resourceLocation = "./";

        const Value &a = jsonConfig;
        if (!a.IsObject()) {
            _WARNING("load resource configuration : Root element must be Object", LOG_CHANNEL::DEFAULT);
            return nullptr;
        }

        conf->m_resourceLocationType = ResourceLocationType::FOLDER;
        if (a.HasMember("resourceLocationType") && a["resourceLocationType"].IsString()) {
            string rlts = a["resourceLocationType"].GetString();
            if (rlts.compare("folder") == 0) {
                conf->m_resourceLocationType = ResourceLocationType::FOLDER;
                _DEBUG("resourceLocationType = FOLDER", LOG_CHANNEL::DEFAULT);
            } else if (rlts.compare("archive") == 0) {
                conf->m_resourceLocationType = ResourceLocationType::ARCHIVE;
                _DEBUG("resourceLocationType = ARCHIVE", LOG_CHANNEL::DEFAULT);
            } else {
                _WARNING("resourceLocationType ignored because of wrong value", LOG_CHANNEL::DEFAULT);
            }
        }

        if (a.HasMember("resourcesLocation") && a["resourcesLocation"].IsString()) {
            conf->m_resourceLocation = a["resourcesLocation"].GetString();
            _DEBUG("resourcesLocation = " << resourceLocation, LOG_CHANNEL::DEFAULT);
        }

        if (a.HasMember("resources") && a["resources"].IsArray()) {
            readResources(a["resources"], conf);
        }

        return unique_ptr<ResourceConfiguration>(conf);
    }

    ResourceLocationType getResourceLocationType() const {
        return m_resourceLocationType;
    }

    string getResourceLocation() const {
        return m_resourceLocation;
    }

    vector<resourceEntry> &getResourceEntries() {
        return m_resources;
    }

private:
    static void readResources(const Value &node, ResourceConfiguration *conf) {
        for (SizeType i = 0; i < node.Size(); i++) {
            readResource(node[i], conf);
        }
    }

    static void readResource(const Value &node, ResourceConfiguration *conf) {
        if (node.IsObject() && node.HasMember("name") && node.HasMember("importer") && node.HasMember("filename")) {
            resourceEntry re;
            re.name = node["name"].GetString();
            re.filename = node["filename"].GetString();
            re.importerName = node["importer"].GetString();

            if (node.HasMember("metadatas") && node["metadatas"].IsArray()) {
                for (SizeType i = 0; i < node["metadatas"].Size(); i++) {
                    const Value& metas = node["metadatas"][i];
                    if (metas.HasMember("key") && metas.HasMember("value") &&
                            metas["key"].IsString() && metas["value"].IsString()) {
                        resourceMetadata metadata;
                        metadata.name = metas["key"].GetString();
                        metadata.name = metas ["value"].GetString();
                        re.metadatas.insert(make_pair(GH_HASH(metadata.name), metadata));
                    }
                    else {
                        _WARNING("Ignored resource's metadata", LOG_CHANNEL::DEFAULT);
                    }
                }
            }

            conf->m_resources.push_back(re);
            _DEBUG("resources [" << re.name << "], importer [" << re.importerName << "], filename [" << re.filename
                                 << "]",
                   LOG_CHANNEL::DEFAULT);
        } else {
            _WARNING("Ignored resource", LOG_CHANNEL::DEFAULT);
        }
    }
};

}
#endif //GANESHENGINE_GHRESOURCECONFIGURATION_H
