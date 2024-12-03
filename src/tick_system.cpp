#include <stdexcept>

#include <LTEngine/tick_system.hpp>


using namespace LTEngine;


TickSystem::TickSystem() {
	m_tickTimer.onEnd += std::bind(&TickSystem::onTimerEnd, this);
	m_tickTimer.setRepeat(true);
}


void TickSystem::step(f32 step) {
	m_tickTimer.step(step);
}


void TickSystem::setTickDelay(f32 delaySeconds) {
	m_tickTimer.stop();
	m_tickTimer.start(delaySeconds);
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


void TickSystem::onTimerEnd() {
	m_currentTick++;
	onTick(m_currentTick);

	for (auto &clock : m_tickClocks) {
		if (m_currentTick % clock.second == 0) { m_tickEvents[clock.first](m_currentTick); }
	}
}
