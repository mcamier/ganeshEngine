#include "ghInputContext.h"

#include "ghInputManager.h"
#include <functional>


namespace ganeshEngine {

int InputContext::m_lastId = 0;

InputContext::InputContext()
{
    m_id = m_lastId++;
    m_bActive = false;
}

InputContext::~InputContext()
{
}

void InputContext::registerMatch(unique_ptr<InputMatch> inputMatch)
{
    m_inputMatches.push_back(move(inputMatch));
}

InputMatch* InputContext::getInputMatch(rawInput &rawInput) const
{
    for (const auto &match : m_inputMatches) {
	if (rawInput.type == RawInput::TYPE::MOVE) {
	    if (match->type == rawInput.type &&
		    match->source == rawInput.source) {
		//shared_ptr<InputMatch> m {new InputMatch((*match.get()))};
		return nullptr;
	    }
	}

	if (rawInput.type == RawInput::TYPE::PRESS ||
		rawInput.type == RawInput::TYPE::RELEASE ||
		rawInput.type == RawInput::TYPE::HOLD) {

	    if (match->type == rawInput.type &&
		    match->source == rawInput.source &&
		    match->key == (RawInput::KEY)rawInput.data.button.key &&
		    match->mods == rawInput.data.button.mods) {
		//shared_ptr<InputMatch> m {new InputMatch((*match.get()))};
		return nullptr;
	    }
	} else {
	    if (match->type == rawInput.type &&
		    match->source == rawInput.source &&
		    match->key == (RawInput::KEY)rawInput.data.button.key) {
		//shared_ptr<InputMatch> m {new InputMatch((*match.get()))};
		return nullptr;
	    }
	}
    }
    return nullptr;
}

int InputContext::getId() const
{
    return m_id;
}

bool InputContext::isActive() const
{
    return m_bActive;
}

void InputContext::setActive(bool active)
{
    m_bActive = active;
}
}