#include "ghInputContext.h"

#include "ghInputManager.h"
#include <functional>


namespace ganeshEngine {

int InputContext::m_lastId = 0;

InputContext::InputContext() {
    m_id = m_lastId++;
    m_bActive = false;
}

InputContext::~InputContext() {}

void InputContext::registerMatch(unique_ptr<InputMatch> inputMatch) {
	m_inputMatches.push_back(move(inputMatch));
}

U32 InputContext::contains(rawInput &rawInput) const {
    for(auto const &match : m_inputMatches) {
        if(rawInput.type == RawInput::TYPE::PRESS ||
           rawInput.type == RawInput::TYPE::RELEASE ||
           rawInput.type == RawInput::TYPE::HOLD) {

            if(match->type == rawInput.type &&
               match->source == rawInput.source &&
               match->key == (RawInput::KEY)rawInput.data.button.key &&
               match->mods == rawInput.data.button.mods ){
                return match->callbackNameHash;
            }
        } else {
            if(match->type == rawInput.type &&
               match->source == rawInput.source &&
               match->key == (RawInput::KEY)rawInput.data.button.key) {
                return match->callbackNameHash;
            }
        }
    }
    return -1;
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