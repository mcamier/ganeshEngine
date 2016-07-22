#ifndef GANESHENGINE_GHINPUTCONFIGURATION_H
#define GANESHENGINE_GHINPUTCONFIGURATION_H

#include "ghHeaders.h"

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
class InputManagerConfiguration {

private:
    int m_chordThresholdDetectionMs = -1;

public:
    static unique_ptr<InputManagerConfiguration> loadFromFile(string configFilename) {
        _INFO("Load InputManager Configuration : " << configFilename, LOG_CHANNEL::INPUT);
        InputManagerConfiguration *conf = new InputManagerConfiguration();
        Document jsonConfig;
        char readBuffer[65536];

        FILE* fp = fopen(configFilename.c_str(), "rb");
        FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        jsonConfig.ParseStream(is);

        const Value& a = jsonConfig;
        assert(a.IsObject());

        if(a.HasMember("chord")) {
            const Value& chord= a["chord"];
            ASSERT(chord.IsObject());

            if(chord.HasMember("threshold_detection_ms")) {
                ASSERT(chord["threshold_detection_ms"].IsInt());
                conf->m_chordThresholdDetectionMs = chord["threshold_detection_ms"].GetInt();
                _INFO("\tthreshold_detection_ms : " << conf->m_chordThresholdDetectionMs, LOG_CHANNEL::INPUT);
            }
        }

        if(a.HasMember("context")) {
            const Value& context = a["context"];
            ASSERT(context.IsArray());
            _INFO("\tInput Matches : ", LOG_CHANNEL::INPUT);

            for (SizeType i = 0; i < context.Size(); i++) {
                const Value& match = context[i];
                ASSERT(match.IsObject());
                ASSERT(match.HasMember("source"));
                ASSERT(match["source"].IsString());
                ASSERT(match.HasMember("type"));
                ASSERT(match["type"].IsString());
                ASSERT(match.HasMember("identifier"));
                ASSERT(match["identifier"].IsString());
                ASSERT(match.HasMember("callbackName"))
                ASSERT(match["callbackName"].IsString());

                InputMatch inputMatch;
                inputMatch.source = RawInput::fromString<RawInput::SOURCE>(match["source"].GetString());
                inputMatch.type = RawInput::fromString<RawInput::TYPE>(match["type"].GetString());
                inputMatch.key = RawInput::fromString<RawInput::KEY>(match["identifier"].GetString());
                inputMatch.callbackNameHash = GH_HASH(match["callbackName"].GetString());
                inputMatch.mods = 0;
            }
        }

        return unique_ptr<InputManagerConfiguration>(conf);
    }

    virtual ~InputManagerConfiguration() {}

private:
    InputManagerConfiguration() {}
};

}

#endif //GANESHENGINE_GHINPUTCONFIGURATION_H
