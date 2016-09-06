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
 * Object containing all informations relative to the configuration of the {@see InputManager}
 */
class InputManagerConfiguration {

private:
    /**
     */
    vector<InputContext*> mInputContexts;

public:
    virtual ~InputManagerConfiguration();

    /**
     * Getter to the vector containing the extracted InputContext*
     * @return vector of InputContext*
     */
    vector<InputContext*> &getInputContexts();

    /**
     * Load a configuration from the filesystem
     *
     * @param configFilename configuration to read
     * @return an inputManagerConfiguration object
     */
    static InputManagerConfiguration loadFromFile(string configFilename);

    /**
     * Write into the input's log channel all the content of the configuration
     */
    void dump();

private:
    /** Object creation only possible through call of the static method :
     * InputManagerConfiguration::loadFromFile */
    InputManagerConfiguration();

    static void readContexts(const Value &node, InputManagerConfiguration *conf);

    static void readContext(const Value &node, InputContext *&ctx);

    static void readMatches(const Value &node, InputContext *ctx);

    static void readMatch(const Value &node, InputMatch *&im);

    static void readChords(const Value &node, InputContext *ctx);

    static Chord *readChord(const Value &node, Chord *&chord);

    static InputMatch readMatchFromChord(const Value &node);
};

}

#endif //GANESHENGINE_GHINPUTCONFIGURATION_H
