#ifndef GANESHENGINE_GHINPUTCONTEXT_H
#define GANESHENGINE_GHINPUTCONTEXT_H

#include "ghHeaders.h"
#include "ghInputUtils.h"
#include <vector>
#include <map>

namespace ganeshEngine {

using namespace std;

class InputManager;

class InputContext {
    friend class InputManager;

private:
    /**
     * Unique ID among all inputContext during on game^s execution
     */
    int m_id;

    /**
     * True if the inputManager should try to match a rawInput against this context, False
     * otherwise
     */
    bool m_bActive;

    /**
     * List of registered inputs in the context
     */
    vector<unique_ptr<InputMatch>> m_inputMatches;

    /**
     * Last id generated
     */
    static int m_lastId;

public:
    InputContext();
    virtual ~InputContext();

    U32 contains(rawInput &rawInput) const;

    void registerMatch(unique_ptr<InputMatch> inputMatch);

    int getId() const;

    bool isActive() const;

private:
    void setActive(bool active);
};

}
#endif //GANESHENGINE_GHINPUTCONTEXT_H
