#ifndef _LTENGINE_TICK_SYSTEM_HPP_
#define _LTENGINE_TICK_SYSTEM_HPP_

#include <string>
#include <unordered_map>

#include <LTEngine/common/types/floattypes.h>
#include <LTEngine/common/types/inttypes.h>

#include <LTEngine/event.hpp>


namespace LTEngine {
	class TickSystem {
	public:
		TickSystem();
		~TickSystem() = default;

		Event<u64> onTick;

		Event<u64, std::string> onSpecificTick;


		void step(f32 step);

		void setTickDelay(f32 delaySeconds);

		u64 getTicks();

		void registerTick(std::string name, u64 everyTicks);
		void unregisterTick(std::string name);

	private:
		u64 m_currentTick = 0;

		f32 m_currentTickTime = 0.f;
		f32 m_tickDelay = 0.05f;

		std::unordered_map<std::string, u64> m_tickClocks;
	};
} // namespace LTEngine

#endif
