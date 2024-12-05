#ifndef _LTENGINE_ANIMATOR_HPP_
#define _LTENGINE_ANIMATOR_HPP_

#include <unordered_map>

#include <LTEngine/animation/animation.hpp>


namespace LTEngine::Animation {
	template <typename T> class Animator {
	public:
		Event<> onAnimationEnd;
		// The signature of the event is (T newState)
		Event<T> onAnimationStateChanged;

		void addAnimation(std::string name, std::unique_ptr<Animation<T>> animation) {
			m_animations[name] = std::move(animation);

			m_animations[name].onAniamtionEnd += [this]() {
				onAnimationEnd();
			};

			m_animations[name].onAnimationStateChanged += [this](T newState) {
				onAnimationStateChanged(newState);
			};
		}
		void removeAnimation(std::string name) { m_animations.erase(name); }
		Animation<T> *getAnimation(std::string name) { return m_animations.get(name); }


		void loadAnimation(std::string name) {
			if (!m_animations.contains(name)) { throw std::runtime_error("Animation not found"); }
			if (m_animations.contains(m_loadedAnimation)) { m_animations[m_loadedAnimation]->stopAnimation(); }
			m_loadedAnimation = name;
		}


		void step(f32 step) {
			if (m_animations.contains(m_loadedAnimation)) { m_animations[m_loadedAnimation]->step(step); }
		}


		void play() {
			if (m_animations.contains(m_loadedAnimation)) { m_animations[m_loadedAnimation]->playAnimation(); }
		}

		void pause() {
			if (m_animations.contains(m_loadedAnimation)) { m_animations[m_loadedAnimation]->pauseAnimation(); }
		}

		void stop() {
			if (m_animations.contains(m_loadedAnimation)) { m_animations[m_loadedAnimation]->stopAnimation(); }
		}


		T getState() {
			if (!m_animations.contains(m_loadedAnimation)) { throw std::runtime_error("Animation not found"); }
			return m_animations[m_loadedAnimation]->getState();
		}

	private:
		std::unordered_map<std::string, std::unique_ptr<Animation<T>>> m_animations;
		std::string m_loadedAnimation = "";
	};
} // namespace LTEngine::Animation

#endif
