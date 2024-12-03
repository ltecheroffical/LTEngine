#include <string>

#include <LTEngine/common/types/floattypes.h>

#include <LTEngine/event.hpp>


#ifndef _LTENGINE_ANIMATION_HPP_
#define _LTENGINE_ANIMATION_HPP_

namespace LTEngine::Animation {
	template <typename T> class Animation {
	public:
		virtual ~Animation() = default;

		Event<> onAnimationEnd;
		Event<T> onAnimationStateChange;

		virtual void step(f32 step) = 0;

		virtual void loadAnimation(std::string animation) = 0;
		virtual void saveAnimation(std::string animation) = 0;

		virtual void playAnimation() = 0;
		virtual void pauseAnimation() = 0;
		virtual void stopAnimation() = 0;

		virtual T getState() = 0;
	};
} // namespace LTEngine::Animation

#endif
