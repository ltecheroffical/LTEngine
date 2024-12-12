#ifndef _LTENGINE_ANIMATION_STATE_MACHINE_HPP_
#define _LTENGINE_ANIMATION_STATE_MACHINE_HPP_

#include <unordered_map>

#include <LTEngine/animation/animator.hpp>

#include <LTEngine/common/types/floattypes.h>
#include <LTEngine/common/types/inttypes.h>


namespace LTEngine::Animation {
	template <typename T> class AnimationStateMachine {

	public:
		AnimationStateMachine(Animator<T> *animator) : m_animator(animator) {}
		~AnimationStateMachine() = default;

		struct StateMachineVariables {
			union VariableVariant {
				bool boolValue;

				void *ptrValue;
				const void *constPtrValue;

				u8 u8Value;
				i8 i8Value;
				u16 u16Value;
				i16 i16Value;
				u32 u32Value;
				i32 i32Value;
				u64 u64Value;
				i64 i64Value;

				f32 f32Value;
				f64 f64Value;
			};

			enum class VariableType {
				Bool = 0,

				Pointer,
				ConstPointer,

				U8,
				I8,
				U16,
				I16,
				U32,
				I32,
				U64,
				I64,

				F32,
				F64
			};


			void setVariable(std::string name, VariableType type, VariableVariant value) {
				m_variableTypes[name] = type;
				m_variableData[name] = value;
			}

			void *getVariable(std::string name, VariableType expectedType) {
				if (!m_variableTypes.contains(name)) { throw std::runtime_error("Variable not found"); }
				if (m_variableTypes[name] != expectedType) { throw std::runtime_error("Variable type mismatch"); }
				return &m_variableData[name];
			}

		private:
			std::unordered_map<std::string, VariableType> m_variableTypes;
			std::unordered_map<std::string, VariableVariant> m_variableData;
		};

		void setVariable(std::string name, bool value) { setVariable(name, StateMachineVariables::VariableType::Bool, value); }
		void setVariable(std::string name, void *value) { setVariable(name, StateMachineVariables::VariableType::Pointer, value); }
		void setVariable(std::string name, const void *value) {
			setVariable(name, StateMachineVariables::VariableType::ConstPointer, value);
		}
		void setVariable(std::string name, u8 value) { setVariable(name, StateMachineVariables::VariableType::U8, value); }
		void setVariable(std::string name, i8 value) { setVariable(name, StateMachineVariables::VariableType::I8, value); }
		void setVariable(std::string name, u16 value) { setVariable(name, StateMachineVariables::VariableType::U16, value); }
		void setVariable(std::string name, i16 value) { setVariable(name, StateMachineVariables::VariableType::I16, value); }
		void setVariable(std::string name, u32 value) { setVariable(name, StateMachineVariables::VariableType::U32, value); }
		void setVariable(std::string name, i32 value) { setVariable(name, StateMachineVariables::VariableType::I32, value); }
		void setVariable(std::string name, u64 value) { setVariable(name, StateMachineVariables::VariableType::U64, value); }
		void setVariable(std::string name, i64 value) { setVariable(name, StateMachineVariables::VariableType::I64, value); }
		void setVariable(std::string name, f32 value) { setVariable(name, StateMachineVariables::VariableType::F32, value); }
		void setVariable(std::string name, f64 value) { setVariable(name, StateMachineVariables::VariableType::F64, value); }

		bool getBoolVariable(std::string name) { return *getVariable(name, StateMachineVariables::VariableType::Bool); }
		void *getPtrVariable(std::string name) { return *getVariable(name, StateMachineVariables::VariableType::Pointer); }
		const void *getConstPtrVariable(std::string name) {
			return *getVariable(name, StateMachineVariables::VariableType::ConstPointer);
		}
		u8 getU8Variable(std::string name) { return *getVariable(name, StateMachineVariables::VariableType::U8); }
		i8 getI8Variable(std::string name) { return *getVariable(name, StateMachineVariables::VariableType::I8); }
		u16 getU16Variable(std::string name) { return *getVariable(name, StateMachineVariables::VariableType::U16); }
		i16 getI16Variable(std::string name) { return *getVariable(name, StateMachineVariables::VariableType::I16); }
		u32 getU32Variable(std::string name) { return *getVariable(name, StateMachineVariables::VariableType::U32); }
		i32 getI32Variable(std::string name) { return *getVariable(name, StateMachineVariables::VariableType::I32); }
		u64 getU64Variable(std::string name) { return *getVariable(name, StateMachineVariables::VariableType::U64); }
		i64 getI64Variable(std::string name) { return *getVariable(name, StateMachineVariables::VariableType::I64); }
		f32 getF32Variable(std::string name) { return *getVariable(name, StateMachineVariables::VariableType::F32); }
		f64 getF64Variable(std::string name) { return *getVariable(name, StateMachineVariables::VariableType::F64); }

		void addTransition(std::string from, std::string to,
		                   std::function<void(const StateMachineVariables *variables)> condition) {
			m_transitions[from] = {to, condition};
		}

		void setAnimation(std::string name) {
			m_animator->loadAnimation(name);
			m_currentAnim = name;
		}


		T getState() { return m_animator->getState(); }

		void step(f32 step) {
			if (m_animator->getCurrentAnimation() != m_currentAnim) { m_animator->loadAnimation(m_currentAnim); }

			if (m_transitions.contains(m_currentAnim)) {
				auto &transition = m_transitions[m_currentAnim];
				if (transition.second && transition.second(&m_variables)) {
					m_currentAnim = transition.first;
					m_animator->loadAnimation(m_currentAnim);

					if (m_isPlaying) {
						m_animator->play();
					} else {
						m_animator->stop();
					}
					if (m_isPaused) {
						m_animator->play();
						m_animator->pause();
					}
				}
			}

			m_animator->step(step);
		}


		void play() {
			m_animator->play();
			m_isPlaying = true;
		}

		void stop() {
			m_animator->stop();
			m_isPlaying = false;
		}

		void pause() {
			m_animator->pause();
			m_isPlaying = false;
			m_isPaused = true;
		}


	private:
		std::unordered_map<std::string, std::pair<std::string, std::function<void(const StateMachineVariables *variables)>>>
		    m_transitions;

		std::string m_currentAnim;

		StateMachineVariables m_variables;
		Animator<T> *m_animator;

		bool m_isPlaying;
		bool m_isPaused;
	};
} // namespace LTEngine::Animation
#endif
