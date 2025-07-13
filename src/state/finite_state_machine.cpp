#include <LTEngine/state/finite_state_machine.hpp>
#include <LTEngine/state/fsm_state.hpp>


using namespace LTEngine;
using namespace LTEngine::State;

void FiniteStateMachine::update(f32 delta) {
	if (_is_in_state) {
		_states[_current_state]->update(delta);
	}
}

void FiniteStateMachine::add_state(const std::string &name, std::unique_ptr<FSMState> state) {
	_states[name] = std::move(state);
}

FSMState *FiniteStateMachine::get_state(const std::string &name) {
	return _states.contains(name) ? _states[name].get() : nullptr;
}

bool FiniteStateMachine::is_in_state(const std::string &name) {
	return _current_state == name && _is_in_state;
}

void FiniteStateMachine::transition(const std::string &name) {
	if (!_states.contains(name)) {
		return;
	}
	if (_is_in_state) {
		_states[_current_state]->on_exit();
	}
	_current_state = name;
	_is_in_state = true;
	if (_states[_current_state]) {
		_states[_current_state]->on_enter();
	}
}
