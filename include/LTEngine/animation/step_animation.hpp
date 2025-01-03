#ifndef _LTENGINE_STEP_ANIMATION_HPP_
#define _LTENGINE_STEP_ANIMATION_HPP_


#include <unordered_map>

#include <LTEngine/animation/animation.hpp>

#include <LTEngine/tick_system.hpp>


namespace LTEngine::Animation {
	template <typename T> class StepAnimation : public Animation<T> {
	public:
		StepAnimation() {
			m_animTicker.onTick += [this](u64 ticks) {
				if (!m_isPlaying) { return; }
				if (!m_frames.contains(ticks)) { return; }
				onAnimationStateChange(m_frames[ticks]);
				m_currentFrame = m_frames[ticks];

				if (std::find_if(m_frames.begin(), m_frames.end(),
				                 [ticks](std::pair<u64, T> frame) { return frame.first > ticks; }) == m_frames.end()) {
					onAnimationEnd();
					stopAnimation();
				}
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


		// Sets what the frame at that tick should be, will stay at the current before triggering the next tick
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
