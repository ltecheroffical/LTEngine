#include <stdexcept>

#include <LTEngine/tick_system.hpp>


using namespace LTEngine;


TickSystem::TickSystem() {
	m_currentTickTime = m_tickDelay;
}


void TickSystem::step(f32 step) {
	if (m_currentTickTime > 0.f) {
		m_currentTickTime -= step;
		return;
	}

	m_currentTickTime = m_tickDelay;
	m_currentTick++;

	if (m_tickCallback != nullptr) { m_tickCallback(m_currentTick); }

	for (auto &clock : m_tickClocks) {
		if (m_currentTick % clock.second.first == 0 && clock.second.second != nullptr) { clock.second.second(m_currentTick); }
	}
}


void TickSystem::setTickDelay(f32 delaySeconds) {
	m_tickDelay = delaySeconds;
}

void TickSystem::setCallback(std::function<void(u64)> callback) {
	m_tickCallback = callback;
}


u64 TickSystem::getTicks() {
	return m_currentTick;
}


void TickSystem::registerTick(std::string name, u64 everyTicks) {
	if (everyTicks == 0) { throw std::runtime_error("`everyTicks` cannot be 0 or it will cause division by zero"); }
	m_tickClocks[name] = std::make_pair(everyTicks, nullptr);
}

void TickSystem::unregisterTick(std::string name) {
	m_tickClocks.erase(name);
}

void TickSystem::setTickCallback(std::function<void(u64)> callback) {
	m_tickCallback = callback;
}
