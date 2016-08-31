#include "ghInputConfiguration.h"

namespace ganeshEngine {

InputManagerConfiguration::~InputManagerConfiguration() {}

InputManagerConfiguration::InputManagerConfiguration() {}

vector<InputContext*> &InputManagerConfiguration::getInputContexts() {
    return m_inputContexts;
}

InputManagerConfiguration InputManagerConfiguration::loadFromFile(string configFilename) {
    _DEBUG("Load InputManager Configuration : " << configFilename, LOG_CHANNEL::INPUT);
    InputManagerConfiguration conf = InputManagerConfiguration();
    Document jsonConfig;
    char readBuffer[65536];

    FILE *fp = fopen(configFilename.c_str(), "rb");
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    jsonConfig.ParseStream(is);

    const Value &a = jsonConfig;
    if (!a.IsObject()) {
        _WARNING("load input configuration : Root element must be Object", LOG_CHANNEL::INPUT);
        exit(-1);
    }

    if (a.HasMember("chord")) {
        readMainDatas(a["chord"], &conf);
    }

    if (a.HasMember("contexts")) {
        readContexts(a["contexts"], &conf);
    }
    return conf;
}

void InputManagerConfiguration::readMainDatas(const Value &node, InputManagerConfiguration *conf) {
    if (!node.IsObject()) {
        _WARNING("load input configuration : Chord root element must be Object", LOG_CHANNEL::INPUT);
        return;
    };
}

void InputManagerConfiguration::readContexts(const Value &node, InputManagerConfiguration *conf) {
    if (!node.IsArray()) {
        _WARNING("load input configuration : contexts must be an array", LOG_CHANNEL::INPUT);
        return;
    };
    _DEBUG("Input configuration", LOG_CHANNEL::INPUT);
    for (SizeType i = 0; i < node.Size(); i++) {
        InputContext *inputContxt = nullptr;
        readContext(node[i], inputContxt);
        if (inputContxt) {
            conf->m_inputContexts.push_back(inputContxt);
        }
    }
}

void InputManagerConfiguration::readContext(const Value &node, InputContext *&ctx) {
    if (!node.IsObject()) {
        _WARNING("load input configuration : context must be an object", LOG_CHANNEL::INPUT);
        return;
    };

    if (node.HasMember("name") && node["name"].IsString()) {
        _DEBUG("Input Contexts: " << node["name"].GetString(), LOG_CHANNEL::INPUT);
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

void InputManagerConfiguration::readMatches(const Value &node, InputContext *ctx) {
    if (!node.IsArray()) {
        _WARNING("load input configuration : matches must be an array", LOG_CHANNEL::INPUT);
        return;
    };

    for (SizeType i = 0; i < node.Size(); i++) {
        InputMatch *inputMatch = nullptr;
        readMatch(node[i], inputMatch);
        if (inputMatch) {
            ctx->registerMatch(*inputMatch);
        }
    }
}

void InputManagerConfiguration::readMatch(const Value &node, InputMatch *&im) {
    if (!node.IsObject() ||
        !node.HasMember("source") || !node["source"].IsString() ||
        !node.HasMember("type") || !node["type"].IsString() ||
        !node.HasMember("code") || !node["code"].IsString() ||
        !node.HasMember("callbackName") || !node["callbackName"].IsString()) {
        _WARNING("load input configuration : input match skipped because it's not well formed",
                 LOG_CHANNEL::INPUT);
        im = nullptr;
        return;
    }
    im = new InputMatch(
            inputDetails::fromString<InputSource>(node["source"].GetString()),
            inputDetails::fromString<InputType>(node["type"].GetString()),
            inputDetails::fromString<InputCode>(node["code"].GetString()),
            GH_HASH(node["callbackName"].GetString()));
}

Chord *InputManagerConfiguration::readChord(const Value &node, Chord *&chord) {
    chord = nullptr;

    if (!node.HasMember("callbackName")) {
        _WARNING("load input configuration : chords must has a callbackName", LOG_CHANNEL::INPUT);
        return chord;
    }
    if (!(node.HasMember("_1") && node.HasMember("_2"))) {
        _WARNING("load input configuration : chord must contains at least two input matche",
                 LOG_CHANNEL::INPUT);
        return chord;
    }

    InputChordSize csize;
    U32 callbackNameHash = GH_HASH(node["callbackName"].GetString());
    InputMatch i1, i2, i3;

    if (node.HasMember("_3")) {
        csize = InputChordSize::_3;
        i1 = readMatchFromChord(node["_1"]);
        i2 = readMatchFromChord(node["_2"]);
        i3 = readMatchFromChord(node["_3"]);
        chord = new Chord(callbackNameHash, i1, i2, i3);
    } else {
        csize = InputChordSize::_2;
        i1 = readMatchFromChord(node["_1"]);
        i2 = readMatchFromChord(node["_2"]);
        chord = new Chord(callbackNameHash, i1, i2);
    }
    if (chord == nullptr) {
        _WARNING("load input configuration : chord skipped because it's not well formed", LOG_CHANNEL::INPUT);
    }
    return chord;
}

InputMatch InputManagerConfiguration::readMatchFromChord(const Value &node) {
    if (!node.IsObject()) {
        _WARNING("load input configuration : chord skipped because it's not well formed", LOG_CHANNEL::INPUT);
        return InputMatch();
    }

    if (!node.HasMember("source") || !node["source"].IsString() ||
        !node.HasMember("type") || !node["type"].IsString() ||
        !node.HasMember("code") || !node["code"].IsString()) {
        _WARNING("load input configuration : input match in chord skipped because it's not well formed",
                 LOG_CHANNEL::INPUT);
        return InputMatch();
    }
    return InputMatch(
            inputDetails::fromString<InputSource>(node["source"].GetString()),
            inputDetails::fromString<InputType>(node["type"].GetString()),
            inputDetails::fromString<InputCode>(node["code"].GetString()),
            0);
}

void InputManagerConfiguration::readChords(const Value &node, InputContext *ctx) {
    if (!node.IsArray()) {
        _WARNING("load input configuration : chords must be an array", LOG_CHANNEL::INPUT);
        return;
    };

    for (SizeType i = 0; i < node.Size(); i++) {
        Chord *chord = nullptr;
        readChord(node[i], chord);

        if (chord) {
            ctx->registerChord(*chord);
        }
    }
}


void InputManagerConfiguration::dump() {
    _DEBUG("Dump of InputManagerConfiguration", LOG_CHANNEL::INPUT);

    for (int i = 0; i < this->m_inputContexts.size(); i++) {
        const auto ptr = this->m_inputContexts[i];
        _DEBUG("\t Input Context : " << ptr->getId() << ", with " << ptr->m_inputMatches.size()
                                     << " input matches", LOG_CHANNEL::INPUT);

        for (int j = 0; j < ptr->m_inputMatches.size(); j++) {
            const auto match = ptr->m_inputMatches[j];
            _DEBUG("\t\t Source = " << inputDetails::toString(match.m_source), LOG_CHANNEL::INPUT);
            _DEBUG("\t\t Type = " << inputDetails::toString(match.m_type), LOG_CHANNEL::INPUT);
            _DEBUG("\t\t Key = " << inputDetails::toString(match.m_code), LOG_CHANNEL::INPUT);
            _DEBUG("\t\t----------------------------", LOG_CHANNEL::INPUT);
        }
        _DEBUG("\t============================", LOG_CHANNEL::INPUT);
    }
    _DEBUG("End Dump of InputManagerConfiguration", LOG_CHANNEL::INPUT);
}

}