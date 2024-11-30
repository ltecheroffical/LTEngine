#include <stdexcept>

#include <LTEngine/tick_system.hpp>


using namespace LTEngine;


TickSystem::TickSystem() {
	m_currentTickTime = m_tickDelay;
}


void TickSystem::step(f32 step) {
	if (m_currentTickTime - step > 0.f) {
		m_currentTickTime -= step;
		return;
	}

	m_currentTickTime = m_tickDelay;
	m_currentTick++;

	onTick(m_currentTick);

	for (auto &clock : m_tickClocks) {
		if (m_currentTick % clock.second == 0) { m_tickEvents[clock.first](m_currentTick); }
	}
}


void TickSystem::setTickDelay(f32 delaySeconds) {
	m_tickDelay = delaySeconds;
}


u64 TickSystem::getTicks() {
	return m_currentTick;
}


void TickSystem::registerTick(std::string name, u64 everyTicks) {
	if (everyTicks == 0) { throw std::runtime_error("`everyTicks` cannot be 0 or it will cause division by zero"); }
	m_tickClocks[name] = everyTicks;
	m_tickEvents[name].clear();
}

void TickSystem::unregisterTick(std::string name) {
	m_tickClocks.erase(name);
	m_tickEvents.erase(name);
}

Event<u64> *TickSystem::getTickEvent(std::string name) {
	return &m_tickEvents[name];
}
