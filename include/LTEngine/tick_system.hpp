#ifndef _LTENGINE_TICK_SYSTEM_HPP_
#define _LTENGINE_TICK_SYSTEM_HPP_

#include <string>
#include <unordered_map>

#include <LTEngine/event.hpp>
#include <LTEngine/timer.hpp>


namespace LTEngine {
	class LTENGINE_API TickSystem {
	public:
		TickSystem();
		~TickSystem() = default;

		/**
		 * @brief Triggered when a tick happens.
		 *
		 * @details
		 * The first argument is the current ticks.
		 */
		Event<u64> onTick;


		void step(f32 step);

		/**
		 * @brief Sets the time between ticks in seconds.
		 */
		void setTickDelay(f32 delaySeconds);

		u64 getTicks();

		void resetTicks() {
			m_currentTick = 0;
		}

		void registerTick(std::string name, u64 everyTicks);
		void unregisterTick(std::string name);
		Event<u64> *getTickEvent(std::string name);

	private:
		void onTimerEnd();

		u64 m_currentTick = 0;

		Timer m_tickTimer;

		std::unordered_map<std::string, u64> m_tickClocks;
		std::unordered_map<std::string, Event<u64>> m_tickEvents;
	};
} // namespace LTEngine

#endif
