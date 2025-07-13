#ifndef _LTENGINE_FINITE_STATE_MACHINE_HPP_
#define _LTENGINE_FINITE_STATE_MACHINE_HPP_

#include <string>
#include <unordered_map>

#include <LTEngine/common/compiler_utils.h>


namespace LTEngine::State {
	class FSMState;
	class LTENGINE_API FiniteStateMachine {
	public:
		FiniteStateMachine() = default;
		~FiniteStateMachine() = default;

		void update(f32 delta);

		void add_state(const std::string &name, std::unique_ptr<FSMState> state);
		FSMState *get_state(const std::string &name);

		bool is_in_state(const std::string &name);
		void transition(const std::string &name);

	private:
		std::string _current_state;
		bool _is_in_state = false;

		std::unordered_map<std::string, std::unique_ptr<FSMState>> _states;
	};
} // namespace LTEngine::State

#endif
