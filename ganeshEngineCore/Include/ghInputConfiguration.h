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

    public:

        virtual ~InputManagerConfiguration() {
        }

        /**
         * Return the maximum amount of time inputs can be held in order to detects chords (input combination)
         *
         * @return amount of time in millisecond
         */
        int getChordThresholdDetectionMs() const {
            return m_chordThresholdDetectionMs;
        }

        vector<unique_ptr<InputContext>> &getInputContexts() {
            return m_inputContexts;
        }

        /**
         * Load a configuration from the filesystem
         * Returns nullptr if the file could not be parsed properly
         *
         * @param configFilename configuration to read
         * @return loaded configuration
         */
        static unique_ptr<InputManagerConfiguration> loadFromFile(string configFilename) {
            _DEBUG("Load InputManager Configuration : " << configFilename, LOG_CHANNEL::INPUT);
            InputManagerConfiguration *conf = new InputManagerConfiguration();
            Document jsonConfig;
            char readBuffer[65536];

            FILE *fp = fopen(configFilename.c_str(), "rb");
            FileReadStream is(fp, readBuffer, sizeof(readBuffer));
            jsonConfig.ParseStream(is);

            const Value &a = jsonConfig;
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
        InputManagerConfiguration() {
        }

        static void readMainDatas(const Value &node, InputManagerConfiguration *conf) {
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
                _DEBUG("threshold_detection_ms : " << conf->m_chordThresholdDetectionMs, LOG_CHANNEL::INPUT);
            }

        }

        static void readContexts(const Value &node, InputManagerConfiguration *conf) {
            if (!node.IsArray()) {
                _WARNING("load input configuration : contexts must be an array", LOG_CHANNEL::INPUT);
                return;
            };
			_DEBUG("Input configuration", LOG_CHANNEL::INPUT);
            for (SizeType i = 0; i < node.Size(); i++) {
                InputContext *inputContxt = nullptr;
                readContext(node[i], inputContxt);
                if (inputContxt) {
                    conf->m_inputContexts.push_back(unique_ptr<InputContext>(inputContxt));
                }
            }
        }

        static void readContext(const Value &node, InputContext *&ctx) {
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

        static void readMatches(const Value &node, InputContext *ctx) {
            if (!node.IsArray()) {
                _WARNING("load input configuration : matches must be an array", LOG_CHANNEL::INPUT);
                return;
            };

            for (SizeType i = 0; i < node.Size(); i++) {
                InputMatch *inputMatch = nullptr;
                readMatch(node[i], inputMatch);
                if (inputMatch) {
					_WARNING("\t - " << RawInput::toString(inputMatch->getSource())<< "/" << RawInput::toString(inputMatch->getType()) << "/"<< RawInput::toString(inputMatch->getKey()),
							 LOG_CHANNEL::INPUT);
                    ctx->registerMatch(unique_ptr<InputMatch>(inputMatch));
                }
            }
        }

        static void readMatch(const Value &node, InputMatch *&im) {
            if (!node.IsObject() ||
                !node.HasMember("source") || !node["source"].IsString() ||
                !node.HasMember("type") || !node["type"].IsString() ||
                !node.HasMember("identifier") || !node["identifier"].IsString() ||
                !node.HasMember("callbackName") || !node["callbackName"].IsString()) {
                _WARNING("load input configuration : input match skipped because it's not well formed",
                         LOG_CHANNEL::INPUT);
                im = nullptr;
                return;
            }
            im = new InputMatch(
                    RawInput::fromString<RawInput::SOURCE>(node["source"].GetString()),
                    RawInput::fromString<RawInput::TYPE>(node["type"].GetString()),
                    RawInput::fromString<RawInput::KEY>(node["identifier"].GetString()),
                    GH_HASH(node["callbackName"].GetString()));
        }

        static Chord* readChord(const Value &node, Chord *&chord) {
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

			CHORD_SIZE csize;
            U32 callbackNameHash = GH_HASH(node["callbackName"].GetString());
			InputMatch i1, i2, i3;


				_DEBUG("Chord action ["<< callbackNameHash <<"] :", LOG_CHANNEL::INPUT);
            if (node.HasMember("_3")) {
				csize = CHORD_SIZE::_3;
				i1 = readMatchFromChord(node["_1"]);
				i2 = readMatchFromChord(node["_2"]);
				i3 = readMatchFromChord(node["_3"]);
				chord = new Chord(callbackNameHash, i1,i2,i3);
				_DEBUG("\t - "<< RawInput::toString(chord->_1.getSource()) <<"/"<< RawInput::toString(chord->_1.getType()) << "/" << RawInput::toString(chord->_1.getKey()), LOG_CHANNEL::INPUT);
				_DEBUG("\t - "<< RawInput::toString(chord->_2.getSource()) <<"/"<< RawInput::toString(chord->_2.getType()) << "/" << RawInput::toString(chord->_2.getKey()), LOG_CHANNEL::INPUT);
				_DEBUG("\t - "<< RawInput::toString(chord->_3.getSource()) <<"/"<< RawInput::toString(chord->_3.getType()) << "/" << RawInput::toString(chord->_3.getKey()), LOG_CHANNEL::INPUT);
            } else {
				csize = CHORD_SIZE::_2;
				i1 = readMatchFromChord(node["_1"]);
				i2 = readMatchFromChord(node["_2"]);
				chord = new Chord(callbackNameHash, i1,i2);
				_DEBUG("\t - "<< RawInput::toString(chord->_1.getSource()) <<"/"<< RawInput::toString(chord->_1.getType()) << "/" << RawInput::toString(chord->_1.getKey()), LOG_CHANNEL::INPUT);
				_DEBUG("\t - "<< RawInput::toString(chord->_2.getSource()) <<"/"<< RawInput::toString(chord->_2.getType()) << "/" << RawInput::toString(chord->_2.getKey()), LOG_CHANNEL::INPUT);
            }
			if (chord == nullptr) {
				_WARNING("load input configuration : chord skipped because it's not well formed", LOG_CHANNEL::INPUT);
			}
			return chord;
        }

        static InputMatch readMatchFromChord(const Value &node) {
            if (!node.IsObject()) {
                _WARNING("load input configuration : chord skipped because it's not well formed", LOG_CHANNEL::INPUT);
                return InputMatch();
            }

            if (!node.HasMember("source") || !node["source"].IsString() ||
                !node.HasMember("type") || !node["type"].IsString() ||
                !node.HasMember("identifier") || !node["identifier"].IsString()) {
                _WARNING("load input configuration : input match in chord skipped because it's not well formed",
                         LOG_CHANNEL::INPUT);
                return InputMatch();
            }
            return InputMatch(
                    RawInput::fromString<RawInput::SOURCE>(node["source"].GetString()),
                    RawInput::fromString<RawInput::TYPE>(node["type"].GetString()),
                    RawInput::fromString<RawInput::KEY>(node["identifier"].GetString()),
                    0);
        }

        static void readChords(const Value &node, InputContext *ctx) {
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
    };

}

#endif //GANESHENGINE_GHINPUTCONFIGURATION_H
