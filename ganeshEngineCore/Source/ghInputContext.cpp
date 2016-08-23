#include "ghInputContext.h"

#include "ghInputManager.h"
#include <functional>


namespace ganeshEngine {

    InputContext::~InputContext() {
    }

    void InputContext::registerMatch(unique_ptr<InputMatch> inputMatch) {
        m_inputMatches.push_back(move(inputMatch));
    }

    void InputContext::registerChord(Chord chord) {
        m_chords.push_back(chord);
    }

    bool InputContext::getInputMatch(rawInput &rawInput, U32 *callbackId) const {
        for (const auto &match : m_inputMatches) {
            if (rawInput.type == RawInput::TYPE::MOVE) {
                if (match->getType() == rawInput.type &&
                    match->getSource() == rawInput.source) {
                    *callbackId = match->getCallbackHash();
                    return true;
                }
            }

            if (rawInput.type == RawInput::TYPE::PRESS ||
                rawInput.type == RawInput::TYPE::RELEASE ||
                rawInput.type == RawInput::TYPE::DOWN) {

                if (match->getType() == rawInput.type &&
                    match->getSource() == rawInput.source &&
                    match->getKey() == (RawInput::KEY) rawInput.data.button.key) {
                    *callbackId = match->getCallbackHash();
                    return true;
                }
            } else {
                if (match->getType() == rawInput.type &&
                    match->getSource() == rawInput.source &&
                    match->getKey() == (RawInput::KEY) rawInput.data.button.key) {
                    *callbackId = match->getCallbackHash();
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