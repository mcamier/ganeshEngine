#ifndef GANESHENGINE_GHRESOURCECONFIGURATION_H
#define GANESHENGINE_GHRESOURCECONFIGURATION_H


#include "ghHeaders.h"
#include "ghResourceUtil.h"

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>
#include <cstring>

namespace ganeshEngine {

using namespace std;
using namespace rapidjson;

/**
 *
 */
class ResourceConfiguration {
private:
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

        const Value &a = jsonConfig;
        if (!a.IsObject()) {
            _WARNING("load resource configuration : Root element must be Object", LOG_CHANNEL::DEFAULT);
            return nullptr;
        }

        if (a.HasMember("resources") && a["resources"].IsArray()) {
            readResources(a["resources"], conf);
        }

        return unique_ptr<ResourceConfiguration>(conf);
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
        if (node.IsObject() && node.HasMember("name") && node.HasMember("loaderName") && node.HasMember("filename")) {
            resourceEntry re;
            re.name = node["name"].GetString();
            re.filename = node["filename"].GetString();
            re.loaderName = node["loaderName"].GetString();

            if (node.HasMember("eagerLoading") && node["eagerLoading"].IsBool()) {
                re.eagerLoading = node["eagerLoading"].GetBool();
            }

            if (node.HasMember("metadatas") && node["metadatas"].IsObject()) {
                const Value &metas = node["metadatas"];
                for (Value::ConstMemberIterator itr = metas.MemberBegin(); itr != metas.MemberEnd(); ++itr) {
                    stringId metaName = gInternString(itr->name.GetString());

                    resourceMetadata metadata;
                    metadata.name = metaName;

                    if (itr->value.IsBool()) {
                        metadata.value.asBool = itr->value.GetBool();
                        re.metadatas.insert(make_pair(metaName, metadata));
                    } else if (itr->value.IsDouble()) {
                        metadata.value.asDouble = itr->value.GetDouble();
                    } else if (itr->value.IsString()) {
                        const char *strvalue = itr->value.GetString();
                        int length = strlen(strvalue);
                        char *ptr = (char *) std::malloc(length * sizeof(char));
                        std::strcpy(ptr, strvalue);
                        metadata.value.asString = ptr;
                        re.metadatas.insert(make_pair(metaName, metadata));
                    } else if (itr->value.IsInt()) {
                        metadata.value.asUInt = itr->value.GetInt();
                        re.metadatas.insert(make_pair(metaName, metadata));
                    } else {
                        _DEBUG("Not valid type for metadata value, this metadata will be ignored",
                               LOG_CHANNEL::RESOURCE);
                    }
                }
            }

            if (node.HasMember("dependencies") && node["dependencies"].IsObject()) {
                const Value &deps = node["dependencies"];
                for (Value::ConstMemberIterator itr = deps.MemberBegin(); itr != deps.MemberEnd(); ++itr) {
                    stringId depName = gInternString(itr->name.GetString());

                    if (itr->value.IsString()) {
                        re.dependencies.insert(make_pair(depName, gInternString(itr->value.GetString())));
                    } else {
                        _DEBUG("Not valid type for metadata value, this metadata will be ignored",
                               LOG_CHANNEL::RESOURCE);
                    }
                }
            }

            conf->m_resources.push_back(re);
            _DEBUG("resources [" << re.name << "], importer [" << re.loaderName << "], filename [" << re.filename
                                 << "]",
                   LOG_CHANNEL::DEFAULT);
        } else {
            _WARNING("Ignored resource", LOG_CHANNEL::DEFAULT);
        }
    }
};

}
#endif //GANESHENGINE_GHRESOURCECONFIGURATION_H
