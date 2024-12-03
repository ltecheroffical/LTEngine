#include <unordered_map>

#include <LTEngine/animation/animation.hpp>

#include <LTEngine/tick_system.hpp>


#ifndef _LTENGINE_STEP_ANIMATION_HPP_
#define _LTENGINE_STEP_ANIMATION_HPP_

namespace LTEngine::Animation {
	template <typename T> class StepAnimation : public Animation<T> {
	public:
		StepAnimation() {
			m_animTicker.onTick += [this](u64 ticks) {
				if (!m_isPlaying) { return; }
				if (!m_frames.contains(ticks)) { return; }
				m_currentFrame = m_frames[ticks];
			};
			m_animTicker.setTickDelay(m_stepsBetweenTicks);
		}

		~StepAnimation() = default;


		void step(f32 step) override {
			if (!m_isPlaying) { return; }

			m_animTicker.step(step);
		}


		void setFrameDelay(f32 delay) {
			m_animTicker.setTickDelay(delay);
			m_stepsBetweenTicks = delay;
		}


		void loadAnimation(std::string animation) override {
			if (!m_animations.contains(animation)) { return; }

			stopAnimation();
			m_frames = m_animations[animation].frames;
			m_stepsBetweenTicks = m_animations[animation].delay;
		}

		void saveAnimation(std::string animation) override {
			m_animations[animation].frames = m_frames;
			m_animations[animation].delay = m_stepsBetweenTicks;
		}


		void playAnimation() override {
			if (!m_isPaused) { m_animTicker.resetTicks(); }

			m_animTicker.setTickDelay(m_stepsBetweenTicks);
			m_isPlaying = true;
			m_isPaused = false;
		}

		void pauseAnimation() override {
			m_isPlaying = false;
			m_isPaused = true;
		}

		void stopAnimation() override {
			m_isPlaying = false;
			m_isPaused = false;
		}


		void setFrame(u64 ticks, T frame) { m_frames[ticks] = frame; }
		void removeFrame(u64 ticks) { m_frames.erase(ticks); }


		T getState() override { return m_currentFrame; }

	private:
		struct CapturedAnimation {
			std::unordered_map<u64, T> frames;
			f32 delay;
		};

		TickSystem m_animTicker;

		f32 m_stepsBetweenTicks = 0.5f;

		bool m_isPlaying = false;
		bool m_isPaused = false;

		T m_currentFrame;
		std::unordered_map<u64, T> m_frames;

		std::unordered_map<std::string, CapturedAnimation> m_animations;
	};
}; // namespace LTEngine::Animation

#endif
