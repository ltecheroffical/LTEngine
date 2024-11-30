#ifndef _LTENGINE_TIMER_HPP_
#define _LTENGINE_TIMER_HPP_

#include <LTEngine/common/types/floattypes.h>

#include <LTEngine/event.hpp>


namespace LTEngine {
	class Timer {
	public:
		Timer() = default;
		~Timer() = default;

		Event<> onEnd;

		void start();
		void start(f32 time);
		void pause();
		void stop();

		void step(f32 timeStep);

		void setRepeat(bool repeat) { m_repeat = repeat; }

		f32 getTimeSet() const { return m_time; }
		f32 getTimeLeft() const { return m_timeLeft; }
		bool isRepeating() const { return m_repeat; }
		bool isRunning() const { return m_running; }

	private:
		bool m_running = false;
		bool m_paused = false;
		bool m_repeat = false;

		f32 m_time = 0.f;
		f32 m_timeLeft = 0.f;
	};
} // namespace LTEngine

#endif
