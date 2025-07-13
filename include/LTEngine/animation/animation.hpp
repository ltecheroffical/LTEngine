#ifndef _LTENGINE_ANIMATION_HPP_
#define _LTENGINE_ANIMATION_HPP_

#include <LTEngine/event.hpp>


namespace LTEngine::Animation {
	template <typename T> class Animation {
	public:
		virtual ~Animation() = default;

		Event<> onAnimationEnd;
		// The signature of the event is (T newState)
		Event<T> onAnimationStateChange;

		virtual void step(f32 step) = 0;

		virtual void playAnimation() = 0;
		virtual void pauseAnimation() = 0;
		virtual void stopAnimation() = 0;

		virtual T getState() = 0;
	};
} // namespace LTEngine::Animation

#endif
