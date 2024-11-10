#pragma once

#include <string>
#include <unordered_map>

#include <LTEngine/common/types/floattypes.h>


namespace LTEngine::State {
    class FSMState;
    class FiniteStateMachine {
    public:
        FiniteStateMachine() = default;
        ~FiniteStateMachine() = default;

        void update(f32 delta);
        
        void addState(const std::string &name, std::unique_ptr<FSMState> state);
        FSMState *getState(const std::string &name);

        bool isInState(const std::string &name);
        void transition(const std::string &name);

    private:
        std::string m_currentState;
        bool m_isInState = false;

        std::unordered_map<std::string, std::unique_ptr<FSMState>> m_states;
    };
}
