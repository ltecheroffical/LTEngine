#include <LTEngine/state/finite_state_machine.hpp>
#include <LTEngine/state/fsm_state.hpp>


using namespace LTEngine;
using namespace LTEngine::State;


void FiniteStateMachine::update(f32 delta) {
    if (m_isInState) {
        m_states[m_currentState]->update(delta);
    }
}


void FiniteStateMachine::addState(const std::string &name, std::unique_ptr<FSMState> state) {
    m_states[name] = std::move(state);
}

FSMState *FiniteStateMachine::getState(const std::string &name) {
    if (!m_states.contains(name)) {
        return nullptr;
    }
    return m_states[name].get();
}


bool FiniteStateMachine::isInState(const std::string &name) {
    return m_currentState == name && m_isInState;
}

void FiniteStateMachine::transition(const std::string &name) {
    if (!m_states.contains(name)) {
        return;
    }
    if (m_isInState) {
        m_states[m_currentState]->onExit();
    }
    m_currentState = name;
    m_isInState = true;
    if (m_states[m_currentState]) {
        m_states[m_currentState]->onEnter();
    }
}
