#ifndef _LTENGINE_TIMER_HPP_
#define _LTENGINE_TIMER_HPP_

#include <LTEngine/event.hpp>


namespace LTEngine {
	class LTENGINE_API Timer {
	public:
		Timer() = default;
		~Timer() = default;

		Event<> on_end;

		void start();
		void start(f32 time);
		void pause();
		void stop();

		void step(f32 time_step);

		void set_repeat(bool repeat) {
			_repeat = repeat;
		}

		f32 get_time_set() const {
			return _time;
		}
		f32 get_time_left() const {
			return _time_left;
		}
		bool is_repeating() const {
			return _repeat;
		}
		bool is_running() const {
			return _running;
		}

	private:
		bool _running = false;
		bool _paused = false;
		bool _repeat = false;

		f32 _time = 0.f;
		f32 _time_left = 0.f;
	};
} // namespace LTEngine

#endif
