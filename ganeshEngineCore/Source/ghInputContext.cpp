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

int InputContext::contains(rawInput &rawInput) const {
    for(auto const &match : m_inputMatches) {
        if(rawInput.type == rawInputType::PRESS ||
           rawInput.type == rawInputType::RELEASE ||
           rawInput.type == rawInputType::HOLD) {

            if(match->type == rawInput.type &&
               match->source == rawInput.source &&
               match->key == rawInput.data.button.key &&
               match->mods == rawInput.data.button.mods ){
                return match->getId();
            }
        } else {
            if(match->type == rawInput.type &&
               match->source == rawInput.source &&
               match->key == rawInput.data.button.key) {
                return match->getId();
            }
        }
    }
    return -1;
}

void InputContext::registerMatch(unique_ptr<InputMatch> inputMatch, function<void(void)> callback) {
    m_inputCallbacks.insert(make_pair(inputMatch->getId(), callback));
    m_inputMatches.push_back(move(inputMatch));
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