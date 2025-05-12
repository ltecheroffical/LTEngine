#ifndef _LTCORE_ANIMATION_HPP_
#define _LTCORE_ANIMATION_HPP_

#include <LTCore/event.hpp>


namespace LTCore::Animation {
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
} // namespace LTCore::Animation

#endif
