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
		Event<u64> on_tick;


		void step(f32 step);

		/**
		 * @brief Sets the time between ticks in seconds.
		 */
		void set_tick_delay(f32 delay_seconds);

		u64 get_ticks();

		void reset_ticks() {
			_current_tick = 0;
		}

		void register_tick(std::string name, u64 every_ticks);
		void unregister_tick(std::string name);
		Event<u64> *get_tick_event(std::string name);

	private:
		void _on_timer_end();

		u64 _current_tick = 0;

		Timer _tick_timer;

		std::unordered_map<std::string, u64> _tick_clocks;
		std::unordered_map<std::string, Event<u64>> _tick_events;
	};
} // namespace LTEngine

#endif
