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
     */
    vector<InputContext*> m_inputContexts;

public:
    virtual ~InputManagerConfiguration();

    /**
     *
     * @return
     */
    vector<InputContext*> &getInputContexts();

    /**
     * Load a configuration from the filesystem
     * Returns nullptr if the file could not be parsed properly
     *
     * @param configFilename configuration to read
     * @return loaded configuration
     */
    static InputManagerConfiguration loadFromFile(string configFilename);

    /**
     * Write the the Input's log channel all the content of the configuration
     */
    void dump();

private:
    /** Object creation only possible through call of the static method :
     * InputManagerConfiguration::loadFromFile */
    InputManagerConfiguration();

    static void readMainDatas(const Value &node, InputManagerConfiguration *conf);

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
