#ifndef _LTENGINE_FSM_STATE_HPP_
#define _LTENGINE_FSM_STATE_HPP_

#include <LTEngine/common/compiler_utils.h>


namespace LTEngine::State {
	class FiniteStateMachine;

	class LTENGINE_API FSMState {
	public:
		FSMState(FiniteStateMachine *machine) : _machine(machine) {
		}
		virtual ~FSMState() = default;

		virtual void on_enter() {
		}
		virtual void on_exit() {
		}

		virtual void update(f32 delta) {
		}

	private:
		FiniteStateMachine *_machine = nullptr;
	};
} // namespace LTEngine::State

#endif
