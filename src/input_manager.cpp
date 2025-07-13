#include <LTEngine/input_manager.hpp>

#include <LTEngine/exceptions/exc_already_exists.hpp>
#include <LTEngine/exceptions/exc_not_found.hpp>

using namespace LTEngine;

void InputManager::addAction(const std::string &action) {
	if (m_actions.contains(action)) {
		throw AlreadyExistsException("Action already exists");
	}
	m_actions[action] = {};
}

void InputManager::removeAction(const std::string &action) {
	if (!m_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	m_actions.erase(action);
}

void InputManager::addActionKey(const std::string &action, ScanCode code) {
	if (!m_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	auto action_it = std::find_if(m_actions.at(action).begin(), m_actions.at(action).end(), [code](const ActionInput &input) {
		return input.type == ActionInput::KeyboardInput && input.key == code;
	});

	if (action_it != m_actions.at(action).end()) {
		return;
	}

	m_actions.at(action).push_back({
	    .key = code,
	    .type = ActionInput::ActionInputType::KeyboardInput,
	});
}

void InputManager::removeActionKey(const std::string &action, ScanCode code) {
	if (!m_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	auto action_it = std::find_if(m_actions.at(action).begin(), m_actions.at(action).end(), [code](const ActionInput &input) {
		return input.type == ActionInput::KeyboardInput && input.key == code;
	});

	if (action_it == m_actions.at(action).end()) {
		throw NotFoundException("Key not found");
	}

	m_actions.at(action).erase(action_it);
}

void InputManager::addActionMouseButton(const std::string &action, MouseButton button) {
	if (!m_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	auto action_it = std::find_if(m_actions.at(action).begin(), m_actions.at(action).end(), [button](const ActionInput &input) {
		return input.type == ActionInput::KeyboardInput && input.mouse == button;
	});

	if (action_it != m_actions.at(action).end()) {
		return;
	}

	m_actions.at(action).push_back({
	    .mouse = button,
	    .type = ActionInput::ActionInputType::MouseInput,
	});
}

void InputManager::removeActionMouseButton(const std::string &action, MouseButton button) {
	if (!m_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	auto action_it = std::find_if(m_actions.at(action).begin(), m_actions.at(action).end(), [button](const ActionInput &input) {
		return input.type == ActionInput::MouseInput && input.mouse == button;
	});

	if (action_it == m_actions.at(action).end()) {
		throw NotFoundException("Key not found");
	}

	m_actions.at(action).erase(action_it);
}

void InputManager::addActionControllerButton(const std::string &action, ControllerButton button) {
	if (!m_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	auto action_it = std::find_if(m_actions.at(action).begin(), m_actions.at(action).end(), [button](const ActionInput &input) {
		return input.type == ActionInput::ControllerInputButton && input.controllerButton == button;
	});

	if (action_it != m_actions.at(action).end()) {
		return;
	}

	m_actions.at(action).push_back({
	    .controllerButton = button,
	    .type = ActionInput::ActionInputType::ControllerInputButton,
	});
}

void InputManager::removeActionControllerButton(const std::string &action, ControllerButton button) {
	if (!m_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	auto action_it = std::find_if(m_actions.at(action).begin(), m_actions.at(action).end(), [button](const ActionInput &input) {
		return input.type == ActionInput::ControllerInputButton && input.controllerButton == button;
	});

	if (action_it == m_actions.at(action).end()) {
		throw NotFoundException("Key not found");
	}

	m_actions.at(action).erase(action_it);
}

void InputManager::addActionControllerAnalogStick(const std::string &action, ControllerAnalogStick stick, Math::Vec2 direction, f32 deadzone) {
	if (!m_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	auto action_it = std::find_if(m_actions.at(action).begin(), m_actions.at(action).end(), [stick, direction](const ActionInput &input) {
		return input.type == ActionInput::KeyboardInput && input.controllerAnalogStick.analogStick == stick && input.controllerAnalogStick.direction == input.controllerAnalogStick.direction;
	});

	if (action_it != m_actions.at(action).end()) {
		return;
	}

	m_actions.at(action).push_back({
	    .controllerAnalogStick = {
	        stick,
	        direction,
	        deadzone},
	    .type = ActionInput::ActionInputType::KeyboardInput,
	});
}

void InputManager::removeActionControllerAnalogStick(const std::string &action, ControllerAnalogStick stick, Math::Vec2 direction) {
	if (!m_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	auto action_it = std::find_if(m_actions.at(action).begin(), m_actions.at(action).end(), [stick, direction](const ActionInput &input) {
		return input.type == ActionInput::ControllerInputAnalogStick && input.controllerAnalogStick.analogStick == stick && input.controllerAnalogStick.direction == direction;
	});

	if (action_it == m_actions.at(action).end()) {
		throw NotFoundException("Key not found");
	}

	m_actions.at(action).erase(action_it);
}

bool InputManager::isActionTriggered(const std::string &action) {
	if (!m_actions.contains(action)) {
		throw NotFoundException("Action not found");
	}

	auto bindings = m_actions.at(action);
	for (ActionInput &input : bindings) {
		switch (input.type) {
			case ActionInput::ActionInputType::KeyboardInput: LTENGINE_RETURN_VALUE_CONDITION(m_isKeyDownCallback(input.key), true); break;
			case ActionInput::ActionInputType::MouseInput: LTENGINE_RETURN_VALUE_CONDITION(m_isMouseButtonDownCallback(input.mouse), true); break;
			case ActionInput::ActionInputType::ControllerInputButton: LTENGINE_RETURN_VALUE_CONDITION(m_isControllerButtonDownCallback(input.controllerButton), true); break;
			case ActionInput::ActionInputType::ControllerInputAnalogStick: {
				Math::Vec2 current = m_getControllerAnalogStickCallback(input.controllerAnalogStick.analogStick);
				Math::Vec2 desired = input.controllerAnalogStick.direction;
				f32 deadzone = input.controllerAnalogStick.deadzone;

				if (current.distance(Math::Vec2::Zero) < deadzone) {
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

void InputManager::setKeyDownCallback(InputManager::IsKeyDownCallback callback) {
	m_isKeyDownCallback = callback;
}

void InputManager::setMouseButtonDownCallback(InputManager::IsMouseButtonDownCallback callback) {
	m_isMouseButtonDownCallback = callback;
}

void InputManager::setControllerButtonDownCallback(InputManager::IsControllerButtonDownCallback callback) {
	m_isControllerButtonDownCallback = callback;
}

void InputManager::setControllerAnalogStickCallback(InputManager::GetControllerAnalogStickCallback callback) {
	m_getControllerAnalogStickCallback = callback;
}
