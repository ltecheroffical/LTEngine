#ifndef _LTENGINE_TICK_SYSTEM_HPP_
#define _LTENGINE_TICK_SYSTEM_HPP_

#include <functional>
#include <string>
#include <unordered_map>

#include <LTEngine/common/types/floattypes.h>
#include <LTEngine/common/types/inttypes.h>


namespace LTEngine {
	class TickSystem {
	public:
		TickSystem();
		~TickSystem() = default;

		void step(f32 step);

		void setTickDelay(f32 delaySeconds);
		void setCallback(std::function<void(u64)> callback);

		u64 getTicks();

		void registerTick(std::string name, u64 everyTicks);
		void unregisterTick(std::string name);
		void setTickCallback(std::string name, std::function<void(u64)> callback);

	private:
		u64 m_currentTick = 0;

		f32 m_currentTickTime = 0.f;
		f32 m_tickDelay = 0.05f;

		std::unordered_map<std::string, std::pair<u64, std::function<void(u64)>>> m_tickClocks;
		std::function<void(u64)> m_tickCallback = nullptr;
	};
} // namespace LTEngine

#endif
