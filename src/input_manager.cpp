#include <LTEngine/input_manager.hpp>

#include <LTEngine/exceptions/exc_already_exists.hpp>
#include <LTEngine/exceptions/exc_not_found.hpp>

using namespace LTEngine;

void InputManager::add_action(const std::string &action) {
	if (_actions.contains(action)) {
		throw AlreadyExistsException("Action already exists");
	}
	_actions[action] = {};
}

void InputManager::remove_action(const std::string &action) {
	if (!_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	_actions.erase(action);
}

void InputManager::add_action_key(const std::string &action, ScanCode code) {
	if (!_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	auto action_it = std::find_if(_actions.at(action).begin(), _actions.at(action).end(), [code](const ActionInput &input) {
		return input.type == ActionInput::KEYBOARD_INPUT && input.key == code;
	});

	if (action_it != _actions.at(action).end()) {
		return;
	}

	_actions.at(action).push_back({
	    .key = code,
	    .type = ActionInput::ActionInputType::KEYBOARD_INPUT,
	});
}

void InputManager::remove_action_key(const std::string &action, ScanCode code) {
	if (!_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	auto action_it = std::find_if(_actions.at(action).begin(), _actions.at(action).end(), [code](const ActionInput &input) {
		return input.type == ActionInput::KEYBOARD_INPUT && input.key == code;
	});

	if (action_it == _actions.at(action).end()) {
		throw NotFoundException("Key not found");
	}

	_actions.at(action).erase(action_it);
}

void InputManager::add_action_mouse_button(const std::string &action, MouseButton button) {
	if (!_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	auto action_it = std::find_if(_actions.at(action).begin(), _actions.at(action).end(), [button](const ActionInput &input) {
		return input.type == ActionInput::KEYBOARD_INPUT && input.mouse == button;
	});

	if (action_it != _actions.at(action).end()) {
		return;
	}

	_actions.at(action).push_back({
	    .mouse = button,
	    .type = ActionInput::ActionInputType::MOUSE_INPUT,
	});
}

void InputManager::remove_action_mouse_button(const std::string &action, MouseButton button) {
	if (!_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	auto action_it = std::find_if(_actions.at(action).begin(), _actions.at(action).end(), [button](const ActionInput &input) {
		return input.type == ActionInput::MOUSE_INPUT && input.mouse == button;
	});

	if (action_it == _actions.at(action).end()) {
		throw NotFoundException("Key not found");
	}

	_actions.at(action).erase(action_it);
}

void InputManager::add_action_controller_button(const std::string &action, ControllerButton button) {
	if (!_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	auto action_it = std::find_if(_actions.at(action).begin(), _actions.at(action).end(), [button](const ActionInput &input) {
		return input.type == ActionInput::CONTROLLER_INPUT_BUTTON && input.controller_button == button;
	});

	if (action_it != _actions.at(action).end()) {
		return;
	}

	_actions.at(action).push_back({
	    .controller_button = button,
	    .type = ActionInput::ActionInputType::CONTROLLER_INPUT_BUTTON,
	});
}

void InputManager::remove_action_controller_button(const std::string &action, ControllerButton button) {
	if (!_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	auto action_it = std::find_if(_actions.at(action).begin(), _actions.at(action).end(), [button](const ActionInput &input) {
		return input.type == ActionInput::CONTROLLER_INPUT_BUTTON && input.controller_button == button;
	});

	if (action_it == _actions.at(action).end()) {
		throw NotFoundException("Key not found");
	}

	_actions.at(action).erase(action_it);
}

void InputManager::add_action_controller_analog_stick(const std::string &action, ControllerAnalogStick stick, Math::Vec2 direction, f32 deadzone) {
	if (!_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	auto action_it = std::find_if(_actions.at(action).begin(), _actions.at(action).end(), [stick, direction](const ActionInput &input) {
		return input.type == ActionInput::KEYBOARD_INPUT && input.controller_analog_stick.analog_stick == stick && input.controller_analog_stick.direction == input.controller_analog_stick.direction;
	});

	if (action_it != _actions.at(action).end()) {
		return;
	}

	_actions.at(action).push_back({
	    .controller_analog_stick = {
	        stick,
	        direction,
	        deadzone},
	    .type = ActionInput::ActionInputType::KEYBOARD_INPUT,
	});
}

void InputManager::remove_action_controller_analog_stick(const std::string &action, ControllerAnalogStick stick, Math::Vec2 direction) {
	if (!_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	auto action_it = std::find_if(_actions.at(action).begin(), _actions.at(action).end(), [stick, direction](const ActionInput &input) {
		return input.type == ActionInput::CONTROLLER_INPUT_ANALOG_STICK && input.controller_analog_stick.analog_stick == stick && input.controller_analog_stick.direction == direction;
	});

	if (action_it == _actions.at(action).end()) {
		throw NotFoundException("Key not found");
	}

	_actions.at(action).erase(action_it);
}

bool InputManager::is_action_triggered(const std::string &action) {
	if (!_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	auto bindings = _actions.at(action);
	for (ActionInput &input : bindings) {
		switch (input.type) {
			case ActionInput::ActionInputType::KEYBOARD_INPUT: LTENGINE_RETURN_VALUE_CONDITION(_is_key_down_callback(input.key), true); break;
			case ActionInput::ActionInputType::MOUSE_INPUT: LTENGINE_RETURN_VALUE_CONDITION(_is_mouse_button_down_callback(input.mouse), true); break;
			case ActionInput::ActionInputType::CONTROLLER_INPUT_BUTTON: LTENGINE_RETURN_VALUE_CONDITION(_is_controller_button_down_callback(input.controller_button), true); break;
			case ActionInput::ActionInputType::CONTROLLER_INPUT_ANALOG_STICK: {
				Math::Vec2 current = _get_controller_analog_stick_callback(input.controller_analog_stick.analog_stick);
				Math::Vec2 desired = input.controller_analog_stick.direction;
				f32 deadzone = input.controller_analog_stick.deadzone;

				if (current.distance(Math::Vec2::ZERO) < deadzone) {
					break;
				}

				f32 dot = current.x * desired.x + current.y * desired.y;
				if (dot > 0.9f) {
					return true;
				}
				break;
			}
		}
	}
	return false;
}

void InputManager::set_key_down_callback(InputManager::is_key_down_callback callback) {
	_is_key_down_callback = callback;
}

void InputManager::set_mouse_button_down_callback(InputManager::is_mouse_button_down_callback callback) {
	_is_mouse_button_down_callback = callback;
}

void InputManager::set_controller_button_down_callback(InputManager::is_controller_button_down_callback callback) {
	_is_controller_button_down_callback = callback;
}

void InputManager::set_controller_analog_stick_callback(InputManager::get_controller_analog_stick_callback callback) {
	_get_controller_analog_stick_callback = callback;
}
