#ifndef _LTENGINE_INPUT_MANAGER_HPP_
#define _LTENGINE_INPUT_MANAGER_HPP_

#include <vector>
#include <functional>
#include <unordered_map>

#include <LTEngine/input.hpp>
#include <LTEngine/math/vec2.hpp>

namespace LTEngine {
class InputManager {
  public:
	InputManager() = default;
	~InputManager() = default;

	using IsKeyDownCallback = std::function<bool(ScanCode key)>;
	using IsMouseButtonDownCallback = std::function<bool(MouseButton button)>;
	using IsControllerButtonDownCallback = std::function<bool(ControllerButton button)>;
	// Expects returned normalized value between 0.0..1.0
	using GetControllerAnalogStickCallback = std::function<Math::Vec2(ControllerAnalogStick stick)>;

	// May throw AlreadyExistsException
	void addAction(const std::string &action);
	// May throw NotFoundException
	void removeAction(const std::string &action);

	// May throw NotFoundException
	void addActionKey(const std::string &action, ScanCode code);
	// May throw NotFoundException
	void removeActionKey(const std::string &action, ScanCode code);

	// May throw NotFoundException
	void addActionMouseButton(const std::string &action, MouseButton button);
	// May throw NotFoundException
	void removeActionMouseButton(const std::string &action, MouseButton button);

	// May throw NotFoundException
	void addActionControllerButton(const std::string &action, ControllerButton button);
	// May throw NotFoundException
	void removeActionControllerButton(const std::string &action, ControllerButton button);

	// May throw NotFoundException
	void addActionControllerAnalogStick(const std::string &action, ControllerAnalogStick stick, Math::Vec2 direction, f32 deadzone);
	// May throw NotFoundException
	void removeActionControllerAnalogStick(const std::string &action, ControllerAnalogStick stick, Math::Vec2 direction);

	// May throw NotFoundException
	bool isActionTriggered(const std::string &action);

	void setKeyDownCallback(IsKeyDownCallback callback);
	void setMouseButtonDownCallback(IsMouseButtonDownCallback callback);
	void setControllerButtonDownCallback(IsControllerButtonDownCallback callback);
	void setControllerAnalogStickCallback(GetControllerAnalogStickCallback callback);

  private:
	struct ActionInput {
		union {
			ScanCode key;
			MouseButton mouse;
			ControllerButton controllerButton;

			struct {
				ControllerAnalogStick analogStick;
				Math::Vec2 direction;
				f32 deadzone;
			} controllerAnalogStick;
		};

		enum ActionInputType {
			KeyboardInput = 0,
			MouseInput,
			ControllerInputButton,
			ControllerInputAnalogStick
		} type;
	};

	IsKeyDownCallback m_isKeyDownCallback;
	IsMouseButtonDownCallback m_isMouseButtonDownCallback;
	IsControllerButtonDownCallback m_isControllerButtonDownCallback;
	GetControllerAnalogStickCallback m_getControllerAnalogStickCallback;

	std::unordered_map<std::string, std::vector<ActionInput>> m_actions;
};
} // namespace LTEngine

#endif // _LTENGINE_INPUT_MANAGER_HPP_
