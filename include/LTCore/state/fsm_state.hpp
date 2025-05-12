#ifndef _LTCORE_FSM_STATE_HPP_
#define _LTCORE_FSM_STATE_HPP_

#include <LTCore/common/compiler_utils.h>


namespace LTCore::State {
	class FiniteStateMachine;

	class LTCORE_API FSMState {
	public:
		FSMState(FiniteStateMachine *machine) : m_machine(machine) {
		}
		virtual ~FSMState() = default;

		virtual void onEnter() {
		}
		virtual void onExit() {
		}

		virtual void update(f32 delta) {
		}

	private:
		FiniteStateMachine *m_machine = nullptr;
	};
} // namespace LTCore::State

#endif
