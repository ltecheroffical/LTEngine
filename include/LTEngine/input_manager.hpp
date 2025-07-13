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

	using is_key_down_callback = std::function<bool(ScanCode key)>;
	using is_mouse_button_down_callback = std::function<bool(MouseButton button)>;
	using is_controller_button_down_callback = std::function<bool(ControllerButton button)>;
	// Expects returned normalized value between 0.0..1.0
	using get_controller_analog_stick_callback = std::function<Math::Vec2(ControllerAnalogStick stick)>;

	// May throw AlreadyExistsException
	void add_action(const std::string &action);
	// May throw NotFoundException
	void remove_action(const std::string &action);

	// May throw NotFoundException
	void add_action_key(const std::string &action, ScanCode code);
	// May throw NotFoundException
	void remove_action_key(const std::string &action, ScanCode code);

	// May throw NotFoundException
	void add_action_mouse_button(const std::string &action, MouseButton button);
	// May throw NotFoundException
	void remove_action_mouse_button(const std::string &action, MouseButton button);

	// May throw NotFoundException
	void add_action_controller_button(const std::string &action, ControllerButton button);
	// May throw NotFoundException
	void remove_action_controller_button(const std::string &action, ControllerButton button);

	// May throw NotFoundException
	void add_action_controller_analog_stick(const std::string &action, ControllerAnalogStick stick, Math::Vec2 direction, f32 deadzone);
	// May throw NotFoundException
	void remove_action_controller_analog_stick(const std::string &action, ControllerAnalogStick stick, Math::Vec2 direction);

	// May throw NotFoundException
	bool is_action_triggered(const std::string &action);

	void set_key_down_callback(is_key_down_callback callback);
	void set_mouse_button_down_callback(is_mouse_button_down_callback callback);
	void set_controller_button_down_callback(is_controller_button_down_callback callback);
	void set_controller_analog_stick_callback(get_controller_analog_stick_callback callback);

  private:
	struct ActionInput {
		union {
			ScanCode key;
			MouseButton mouse;
			ControllerButton controller_button;

			struct {
				ControllerAnalogStick analog_stick;
				Math::Vec2 direction;
				f32 deadzone;
			} controller_analog_stick;
		};

		enum ActionInputType {
			KEYBOARD_INPUT = 0,
			MOUSE_INPUT,
			CONTROLLER_INPUT_BUTTON,
			CONTROLLER_INPUT_ANALOG_STICK
		} type;
	};

	is_key_down_callback _is_key_down_callback;
	is_mouse_button_down_callback _is_mouse_button_down_callback;
	is_controller_button_down_callback _is_controller_button_down_callback;
	get_controller_analog_stick_callback _get_controller_analog_stick_callback;

	std::unordered_map<std::string, std::vector<ActionInput>> _actions;
};
} // namespace LTEngine

#endif // _LTENGINE_INPUT_MANAGER_HPP_
