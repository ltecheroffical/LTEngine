#ifndef _LTENGINE_EVENT_HPP_
#define _LTENGINE_EVENT_HPP_

#include <functional>
#include <vector>

#include <LTEngine/common/compiler_utils.h>


namespace LTEngine {
	template <typename... args_ty> class LTENGINE_API Event {
	public:
		Event() = default;
		~Event() = default;


		void invoke(args_ty... args) {
			for (auto &listener : _listeners) {
				listener(args...);
			}
		}

		void listen(std::function<void(args_ty...)> listener) {
			_listeners.push_back(listener);
		}
		void unlisten(std::function<void(args_ty...)> listener) {
			_listeners.erase(std::remove(_listeners.begin(), _listeners.end(), listener), _listeners.end());
		}

		void clear() {
			_listeners.clear();
		}


		void operator+=(std::function<void(args_ty...)> listener) {
			listen(listener);
		}
		void operator-=(std::function<void(args_ty...)> listener) {
			unlisten(listener);
		}

		void operator()(args_ty... args) {
			invoke(args...);
		}

	private:
		std::vector<std::function<void(args_ty...)>> _listeners;
	};
} // namespace LTEngine

#endif
