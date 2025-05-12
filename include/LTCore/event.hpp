#ifndef _LTCORE_EVENT_HPP_
#define _LTCORE_EVENT_HPP_

#include <functional>
#include <vector>

#include <LTCore/common/compiler_utils.h>


namespace LTCore {
	template <typename... argsTy> class LTCORE_API Event {
	public:
		Event() = default;
		~Event() = default;


		void invoke(argsTy... args) {
			for (auto &listener : m_listeners) {
				listener(args...);
			}
		}

		void listen(std::function<void(argsTy...)> listener) {
			m_listeners.push_back(listener);
		}
		void unlisten(std::function<void(argsTy...)> listener) {
			m_listeners.erase(std::remove(m_listeners.begin(), m_listeners.end(), listener), m_listeners.end());
		}

		void clear() {
			m_listeners.clear();
		}


		void operator+=(std::function<void(argsTy...)> listener) {
			listen(listener);
		}
		void operator-=(std::function<void(argsTy...)> listener) {
			unlisten(listener);
		}

		void operator()(argsTy... args) {
			invoke(args...);
		}

	private:
		std::vector<std::function<void(argsTy...)>> m_listeners;
	};
} // namespace LTCore

#endif
