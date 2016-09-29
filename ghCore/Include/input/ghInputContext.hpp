#ifndef GANESHENGINE_GHINPUTCONTEXT_H
#define GANESHENGINE_GHINPUTCONTEXT_H

#include "input/ghInputUtils.hpp"

#include <vector>
#include <map>

namespace ganeshEngine {

    using namespace std;

    class InputManager;

    class InputContext {
        friend class InputManager;
        friend class InputManagerConfiguration;

    private:
        /**
         * Unique ID among all inputContext during on game^s execution
         */
        stringId m_id;

        /**
         * True if the inputManager should try to match a RawInput against this context, False
         * otherwise
         */
        bool m_bActive;

        /**
         * List of registered inputs in the context
         */
        vector<InputMatch> m_inputMatches;

        vector<Chord> m_chords;

    public:
        InputContext(stringId id);

        virtual ~InputContext();

        bool getInputMatch(const RawInput &RawInput, stringId *callback) const;

        void registerMatch(InputMatch inputMatch);

        void registerChord(Chord chord);

        int getId() const;

        bool isActive() const;

    private:
        void setActive(bool active);
    };

}
#endif //GANESHENGINE_GHINPUTCONTEXT_H
