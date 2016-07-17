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
        _INFO("Load InputManager Configuration : " << configFilename);
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
            assert(chord.IsObject());

            if(chord.HasMember("threshold_detection_ms")) {
                assert(chord["threshold_detection_ms"].IsInt());
                conf->m_chordThresholdDetectionMs = chord["threshold_detection_ms"].GetInt();
                _INFO("\tthreshold_detection_ms : " << conf->m_chordThresholdDetectionMs);
            }
        }

        if(a.HasMember("context")) {
            const Value& context = a["context"];
            assert(context.IsArray());
            _INFO("\tInput Matches : ");

            for (SizeType i = 0; i < context.Size(); i++) {
                assert(context[i].IsObject());
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
