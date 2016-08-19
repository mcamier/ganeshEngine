#include "ghHeaders.h"
#include "ghSystem.h"


#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>

namespace ganeshEngine {

using namespace std;
using namespace rapidjson;

/**
 *
 */
class GameResource {
public:
	U32 m_resourceId;
	bool m_bLoaded;
	void* m_obj;
};

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
	string m_resourcesLocation;
	map<U32, GameResource> m_resources;

	ResourceConfiguration() {}
public:
	virtual ~ResourceConfiguration() {}

	static unique_ptr<ResourceConfiguration> loadFromFile(string configFilename) {
		_DEBUG("Load Resource Configuration : " << configFilename, LOG_CHANNEL::INPUT);
		ResourceConfiguration *conf = nullptr;
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

		if(a.HasMember("resourceLocationType") && a["resourceLocationType"].IsString()) {
			string rlts = a["resourceLocationType"].GetString();
			if(rlts.compare("FOLDER") == 0) {
				resourceLocationType = ResourceLocationType::FOLDER;
				_DEBUG("resourceLocationType = FOLDER", LOG_CHANNEL::DEFAULT);
			} else if(rlts.compare("ARCHIVE") == 0) {
				resourceLocationType = ResourceLocationType::ARCHIVE;
				_DEBUG("resourceLocationType = ARCHIVE", LOG_CHANNEL::DEFAULT);
			} else {
				_WARNING("resourceLocationType ignored because of wrong value", LOG_CHANNEL::DEFAULT);
			}
		}

		if(a.HasMember("resourcesLocation") && a["resourcesLocation"].IsString()) {
			resourceLocation = a["resourcesLocation"].GetString();
			_DEBUG("resourcesLocation = " << resourceLocation, LOG_CHANNEL::DEFAULT);
		}

		if(a.HasMember("resources") && a["resources"].IsArray()) {
			readResources(a["resources"]);
		}

		return unique_ptr<ResourceConfiguration>(conf);
	}

	ResourceLocationType getResourceLocationType() const {
		return m_resourceLocationType;
	}

	string getResourceLocation() const {
		return m_resourcesLocation;
	}

private:
	static void readResources(const Value &node) {
		for (SizeType i = 0; i < node.Size(); i++) {
			readResource(node[i]);
		}
	}

	static void readResource(const Value &node) {
		if(node.IsObject() && node.HasMember("name") && node.HasMember("importer") && node.HasMember("filename")) {
			string name = node["name"].GetString();
			string importer =node["importer"].GetString();
			string filename = node["filename"].GetString();
			_DEBUG("resources [" << name << "], importer [" << importer << "], filename [" << filename << "]", LOG_CHANNEL::DEFAULT);
		}
		else {
			_WARNING("Ignored resource", LOG_CHANNEL::DEFAULT);
		}
	}
};

/**
 *
 */
class ResourceManager : public System<ResourceManager> {
	friend class System<ResourceManager>;

private:
	/**
	 * Configuration object, holding all informations used to initialization
	 * the manager
	 */
	unique_ptr<ResourceConfiguration> m_configuration;

	ResourceLocationType m_resourceLocationType;

	string m_resourceLocation;

	map<U32, GameResource> m_resources;

private:
	ResourceManager() {}
	ResourceManager(unique_ptr<ResourceConfiguration> conf) : m_configuration(move(conf)) {}

public:
	ResourceManager(const ResourceManager &) = delete;
	ResourceManager &operator=(const ResourceManager &) = delete;
	virtual ~ResourceManager() {}

protected:
	void vInitialize();
	void vDestroy();
};

extern ResourceManager &(*gResource)();
}