#include <cmath>

#include <LTEngine/common/types/inttypes.h>

#include <LTEngine/timer.hpp>


using namespace LTEngine;


void Timer::start(f32 time) {
	_running = true;
	_time_left = time;
	_time = time;
}

void Timer::stop() {
	_running = false;
	_time_left = 0.f;
	_time = 0.f;
}


void Timer::step(f32 time_step) {
	if (!_running) { return; }

	if (_time_left > time_step) {
		_time_left -= time_step;
		return;
	}

	if (!_repeat) {
		_time_left = 0.f;
		on_end();
	} else {
		// Lag compensation -- trigger multiple times if needed
		u32 trigger_count = (u32)(time_step / _time_left);

		for (u32 i = 0; i < trigger_count; i++) { on_end(); }
		_time_left = _time - fmodf(time_step, _time_left);
	}
}
