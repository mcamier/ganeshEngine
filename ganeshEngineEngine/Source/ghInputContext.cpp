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

    bool InputContext::getInputMatch(const RawInput &rawInput, stringId *callbackId) const {
        *callbackId = 0;
        bool matchFound = false;
        for (auto &&match : m_inputMatches) {
            matchFound = match.isMatch(rawInput);
            if(matchFound) {
                *callbackId = match.m_callbackId;
                break;
            }
        }
        return matchFound ;
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