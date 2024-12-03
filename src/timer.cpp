#include <cmath>

#include <LTEngine/common/types/inttypes.h>

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

	if (m_timeLeft > timeStep) {
		m_timeLeft -= timeStep;
		return;
	}

	if (!m_repeat) {
		m_timeLeft = 0.f;
		onEnd();
	} else {
		// Lag compensation -- trigger multiple times if needed
		u32 triggerCount = (u32)(timeStep / m_timeLeft);

		for (u32 i = 0; i < triggerCount; i++) { onEnd(); }
		m_timeLeft = m_time - fmodf(timeStep, m_timeLeft);
	}
}
