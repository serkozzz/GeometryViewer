#include "InputController.h"

#include <glfw3.h>

using namespace gv::Engine;

InputController::InputController(const IInputListener* listener) :
	_listener(listener)
{
}

InputController::~InputController()
{
}

void InputController::checkInput()
{
	if (glfwGetKey(_window, GLFW_KEY_UP ) == GLFW_PRESS){
		_listener->keyPressed(gvKey::GV_KEY_UP);
	}

	if (glfwGetKey(_window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		_listener->keyPressed(gvKey::GV_KEY_DOWN);
	}

	if (glfwGetKey(_window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		_listener->keyPressed(gvKey::GV_KEY_RIGHT);
	}

	if (glfwGetKey(_window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		_listener->keyPressed(gvKey::GV_KEY_LEFT);
	}
}
