#ifndef GANESHENGINE_GHINPUTCONFIGURATION_H
#define GANESHENGINE_GHINPUTCONFIGURATION_H

#include "ghHeaders.h"

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "ghInputUtils.h"
#include "ghInputContext.h"
#include <cstdio>

namespace ganeshEngine {

using namespace std;
using namespace rapidjson;

/**
 *
 */
class InputManagerConfiguration {
private:
    /**
     * maximum amount of time inputs can be held in order to detects chords
     */
    int m_chordThresholdDetectionMs = -1;

    /**
     */
    vector<unique_ptr<InputContext>> m_inputContexts;

    /**
     */
    //vector<unique_ptr<InputMatch>> m_inputMatches;

    /**
     */
    //vector<unique_ptr<Chord>> m_chords;

public:

    virtual ~InputManagerConfiguration()
    {
    }

    /**
     * Return the maximum amount of time inputs can be held in order to detects chords (input combination)
     *
     * @return amount of time in millisecond
     */
    int getChordThresholdDetectionMs() const
    {
	return m_chordThresholdDetectionMs;
    }

    vector<unique_ptr<InputContext>> &getInputContexts()
    {
	return m_inputContexts;
    }

    /**
     * Load a configuration from the filesystem
     * Returns nullptr if the file could not be parsed properly
     *
     * @param configFilename configuration to read
     * @return loaded configuration
     */
    static unique_ptr<InputManagerConfiguration> loadFromFile(string configFilename)
    {
	_DEBUG("Load InputManager Configuration : " << configFilename, LOG_CHANNEL::INPUT);
	InputManagerConfiguration *conf = new InputManagerConfiguration();
	Document jsonConfig;
	char readBuffer[65536];

	FILE* fp = fopen(configFilename.c_str(), "rb");
	FileReadStream is(fp, readBuffer, sizeof (readBuffer));
	jsonConfig.ParseStream(is);

	const Value& a = jsonConfig;
	if (!a.IsObject()) {
	    _WARNING("load input configuration : Root element must be Object", LOG_CHANNEL::INPUT);
	    return nullptr;
	}

	if (a.HasMember("chord")) {
	    readMainDatas(a["chord"], conf);
	}

	if (a.HasMember("contexts")) {
	    readContexts(a["contexts"], conf);
	}
	return unique_ptr<InputManagerConfiguration>(conf);
    }

private:

    /**
     * Object creation only possible through call of the static method : InputManagerConfiguration::loadFromFile
     */
    InputManagerConfiguration()
    {
    }

    static void readMainDatas(const Value& node, InputManagerConfiguration *conf)
    {
	if (!node.IsObject()) {
	    _WARNING("load input configuration : Chord root element must be Object", LOG_CHANNEL::INPUT);
	    return;
	};

	if (node.HasMember("threshold_detection_ms")) {
	    if (!node["threshold_detection_ms"].IsInt()) {
		_WARNING("load input configuration : threshold_detection_ms must be an int", LOG_CHANNEL::INPUT);
		return;
	    };
	    conf->m_chordThresholdDetectionMs = node["threshold_detection_ms"].GetInt();
	    _DEBUG("\tthreshold_detection_ms : " << conf->m_chordThresholdDetectionMs, LOG_CHANNEL::INPUT);
	}

    }

    static void readContexts(const Value& node, InputManagerConfiguration *conf)
    {
	if (!node.IsArray()) {
	    _WARNING("load input configuration : contexts must be an array", LOG_CHANNEL::INPUT);
	    return;
	};

	for (SizeType i = 0; i < node.Size(); i++) {
	    InputContext *inputContxt = nullptr;
	    readContext(node[i], inputContxt);
	    if (inputContxt) {
		conf->m_inputContexts.push_back(unique_ptr<InputContext>(inputContxt));
	    }
	}
    }

    static void readContext(const Value& node, InputContext *&ctx)
    {
	if (!node.IsObject()) {
	    _WARNING("load input configuration : context must be an object", LOG_CHANNEL::INPUT);
	    return;
	};
	_DEBUG("\tInput Matches : ", LOG_CHANNEL::INPUT);

	if (node.HasMember("name") && node["name"].IsString()) {
	    ctx = new InputContext(GH_HASH(node["name"].GetString()));
	    if (node.HasMember("chords")) {
		readChords(node["chords"], ctx);
	    }
	    if (node.HasMember("matches")) {
		readMatches(node["matches"], ctx);
	    }
	} else {
	    _WARNING("load input configuration : context must be named", LOG_CHANNEL::INPUT);
	    return;
	}
    }

    static void readMatches(const Value& node, InputContext *ctx)
    {
	if (!node.IsArray()) {
	    _WARNING("load input configuration : matches must be an array", LOG_CHANNEL::INPUT);
	    return;
	};

	for (SizeType i = 0; i < node.Size(); i++) {
	    InputMatch *inputMatch = nullptr;
	    readMatch(node[i], inputMatch);
	    if (inputMatch) {
		ctx->registerMatch(unique_ptr<InputMatch>(inputMatch));
	    }
	}
    }

    static void readMatch(const Value& node, InputMatch *&im)
    {
	if (!node.IsObject() ||
		!node.HasMember("source") || !node["source"].IsString() ||
		!node.HasMember("type") || !node["type"].IsString() ||
		!node.HasMember("identifier") || !node["identifier"].IsString() ||
		!node.HasMember("callbackName") || !node["callbackName"].IsString()) {
	    _WARNING("load input configuration : input match skipped because it's not well formed", LOG_CHANNEL::INPUT);
	    im = nullptr;
	    return;
	}
	im = new InputMatch();
	im->source = RawInput::fromString<RawInput::SOURCE>(node["source"].GetString());
	im->type = RawInput::fromString<RawInput::TYPE>(node["type"].GetString());
	im->key = RawInput::fromString<RawInput::KEY>(node["identifier"].GetString());
	//im->callbackNameHash = GH_HASH(node["callbackName"].GetString());
	im->mods = 0;
    }

    static void readChord(const Value& node, Chord *&chord)
    {
	chord = nullptr;

	if (!node.HasMember("callbackName")) {
	    _WARNING("load input configuration : chords must has a callbackName", LOG_CHANNEL::INPUT);
	    return;
	}
	if (!(node.HasMember("_1") && node.HasMember("_2"))) {
	    _WARNING("load input configuration : chord must contains at least two input matche", LOG_CHANNEL::INPUT);
	    return;
	}

	chord = new Chord();
	//chord->callbackNameHash = GH_HASH(chord["callbackName"].GetString());
	if (node.HasMember("_3")) {
	    chord->size = CHORD_SIZE::_3;
	} else {
	    chord->size = CHORD_SIZE::_2;
	}
	for (int i = 1; i <= (int) chord->size; i++) {
	    char const *nodeName;
	    switch (chord->size) {
	    case CHORD_SIZE::_2:
		nodeName = "_2";
		break;
	    case CHORD_SIZE::_3:
		nodeName = "_3";
		break;
	    }
	    InputMatch *im = nullptr;
	    readMatchFromChord(node[nodeName], im);
	    if (im) {
		switch (i) {
		case 1:
		    chord->_1 = unique_ptr<InputMatch>(im);
		    break;
		case 2:
		    chord->_2 = unique_ptr<InputMatch>(im);
		    break;
		case 3:
		    chord->_3 = unique_ptr<InputMatch>(im);
		    break;
		}
	    } else {
		_WARNING("load input configuration : chord skipped because it's not well formed", LOG_CHANNEL::INPUT);
		chord = nullptr;
	    }
	}
    }

    static void readMatchFromChord(const Value& node, InputMatch *&im)
    {
	im = nullptr;
	if (!node.IsObject()) {
	    _WARNING("load input configuration : chord skipped because it's not well formed", LOG_CHANNEL::INPUT);
	    return;
	}

	if (!node.HasMember("source") || !node["source"].IsString() ||
		!node.HasMember("type") || !node["type"].IsString() ||
		!node.HasMember("identifier") || !node["identifier"].IsString()) {
	    _WARNING("load input configuration : input match in chord skipped because it's not well formed", LOG_CHANNEL::INPUT);
	    return;
	}
	im = new InputMatch();
	im->source = RawInput::fromString<RawInput::SOURCE>(node["source"].GetString());
	im->type = RawInput::fromString<RawInput::TYPE>(node["type"].GetString());
	im->key = RawInput::fromString<RawInput::KEY>(node["identifier"].GetString());
	im->mods = 0;
    }

    static void readChords(const Value& node, InputContext *ctx)
    {
	if (!node.IsArray()) {
	    _WARNING("load input configuration : chords must be an array", LOG_CHANNEL::INPUT);
	    return;
	};

	for (SizeType i = 0; i < node.Size(); i++) {
	    Chord *chord = nullptr;
	    //readChord(node[i], chord);

	    if (chord) {
		ctx->registerChord(unique_ptr<Chord>(chord));
	    }
	}
    }
};

}

#endif //GANESHENGINE_GHINPUTCONFIGURATION_H
