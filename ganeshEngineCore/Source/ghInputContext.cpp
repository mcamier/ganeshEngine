#include "ghInputContext.h"

#include "ghInputManager.h"
#include <functional>


namespace ganeshEngine {

InputContext::~InputContext()
{
}

void InputContext::registerMatch(unique_ptr<InputMatch> inputMatch)
{
    m_inputMatches.push_back(move(inputMatch));
}

void InputContext::registerChord(unique_ptr<Chord> chord)
{
    m_chords.push_back(move(chord));
}

bool InputContext::getInputMatch(rawInput &rawInput, U32 *callbackId) const
{
    for (const auto &match : m_inputMatches) {
	if (rawInput.type == RawInput::TYPE::MOVE) {
	    if (match->type == rawInput.type &&
		    match->source == rawInput.source) {
		*callbackId = match->callbackNameHash;
		return true;
	    }
	}

	if (rawInput.type == RawInput::TYPE::PRESS ||
		rawInput.type == RawInput::TYPE::RELEASE ||
		rawInput.type == RawInput::TYPE::HOLD) {

	    if (match->type == rawInput.type &&
		    match->source == rawInput.source &&
		    match->key == (RawInput::KEY)rawInput.data.button.key &&
		    match->mods == rawInput.data.button.mods) {
		*callbackId = match->callbackNameHash;
		return true;
	    }
	} else {
	    if (match->type == rawInput.type &&
		    match->source == rawInput.source &&
		    match->key == (RawInput::KEY)rawInput.data.button.key) {
		*callbackId = match->callbackNameHash;
		return true;
	    }
	}
    }
    return false;
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