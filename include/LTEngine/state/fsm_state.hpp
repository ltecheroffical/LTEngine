#ifndef _LTENGINE_FSM_STATE_HPP_
#define _LTENGINE_FSM_STATE_HPP_

#include <LTEngine/common/types/floattypes.h>


namespace LTEngine::State {
	class FiniteStateMachine;

	class FSMState {
	public:
		FSMState(FiniteStateMachine *machine) : m_machine(machine) {}
		virtual ~FSMState() = default;

		virtual void onEnter() {}
		virtual void onExit() {}

		virtual void update(f32 delta) {}

	private:
		FiniteStateMachine *m_machine = nullptr;
	};
} // namespace LTEngine::State

#endif
