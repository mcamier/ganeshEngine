#include "ghInputContext.h"

#include "ghInputManager.h"
#include <functional>


namespace ganeshEngine {

    InputContext::~InputContext() {
    }

    void InputContext::registerMatch(InputMatch inputMatch) {
        m_inputMatches.push_back(inputMatch);
    }

    void InputContext::registerChord(Chord chord) {
        m_chords.push_back(chord);
    }

    bool InputContext::getInputMatch(rawInput &rawInput, U32 *callbackId) const {
        for (auto &&match : m_inputMatches) {
            if (rawInput.type == RawInput::TYPE::MOVE) {
                if (match.m_type == rawInput.type &&
                    match.m_source == rawInput.source) {
                    *callbackId = match.m_callbackNameHash;
                    return true;
                }
            }

            if (rawInput.type == RawInput::TYPE::PRESS ||
                rawInput.type == RawInput::TYPE::RELEASE) {

                if (match.m_type == rawInput.type &&
                    match.m_source == rawInput.source &&
                    match.m_key == (RawInput::KEY) rawInput.key) {
                    *callbackId = match.m_callbackNameHash;
                    return true;
                }
            } else if(rawInput.type == RawInput::TYPE::DOWN) {
                if ( (match.m_type == RawInput::TYPE::DOWN || match.m_type == RawInput::TYPE::PRESS) &&
                    match.m_source == rawInput.source &&
                    match.m_key == (RawInput::KEY) rawInput.key) {
                    *callbackId = match.m_callbackNameHash;
                    return true;
                }
            } else {
                if (match.m_type == rawInput.type &&
                    match.m_source == rawInput.source &&
                    match.m_key == (RawInput::KEY) rawInput.key) {
                    *callbackId = match.m_callbackNameHash;
                    return true;
                }
            }
        }
        return false;
    }

    int InputContext::getId() const {
        return m_id;
    }

    bool InputContext::isActive() const {
        return m_bActive;
    }

    void InputContext::setActive(bool active) {
        m_bActive = active;
    }
}