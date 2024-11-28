#include <LTEngine/timer.hpp>


using namespace LTEngine;


void Timer::start(f32 time) {
	m_running = true;
	m_timeLeft = time;
	m_time = time;
}

void Timer::stop() {
	m_running = false;
	m_timeLeft = 0.f;
	m_time = 0.f;
}


void Timer::step(f32 timeStep) {
	if (!m_running) { return; }
	if (m_timeLeft <= timeStep) {
		m_timeLeft = m_repeat ? m_time : 0.f;
		if (!m_repeat) { m_running = false; }
		onEnd();
		return;
	}
	m_timeLeft -= timeStep;
}
