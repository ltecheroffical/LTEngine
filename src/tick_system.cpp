#include <stdexcept>

#include <LTEngine/tick_system.hpp>


using namespace LTEngine;


TickSystem::TickSystem() {
	_tick_timer.on_end += std::bind(&TickSystem::_on_timer_end, this);
	_tick_timer.set_repeat(true);
}


void TickSystem::step(f32 step) {
	_tick_timer.step(step);
}


void TickSystem::set_tick_delay(f32 delay_seconds) {
	_tick_timer.stop();
	_tick_timer.start(delay_seconds);
}


u64 TickSystem::get_ticks() {
	return _current_tick;
}


void TickSystem::register_tick(std::string name, u64 every_ticks) {
	if (every_ticks == 0) { throw std::runtime_error("`everyTicks` cannot be 0 or it will cause division by zero"); }
	_tick_clocks[name] = every_ticks;
	_tick_events[name].clear();
}

void TickSystem::unregister_tick(std::string name) {
	_tick_clocks.erase(name);
	_tick_events.erase(name);
}

Event<u64> *TickSystem::get_tick_event(std::string name) {
	return &_tick_events[name];
}


void TickSystem::_on_timer_end() {
	_current_tick++;
	on_tick(_current_tick);

	for (auto &clock : _tick_clocks) {
		if (_current_tick % clock.second == 0) { _tick_events[clock.first](_current_tick); }
	}
}
