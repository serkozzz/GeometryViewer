
#include <glfw3.h>
#include <math.h>

#include "InputController.h"

using namespace gv;
using namespace gv::Engine;

InputController::InputController(GLFWwindow* window, const IInputListener* listener) 
	: _window(window), _listener(listener), _cursorInaccuracy(0.00001)
{
	glfwGetWindowSize(_window, &_windowWidth, &_windowHeight);
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

	double xpos, ypos;
	glfwGetCursorPos(_window, &xpos, &ypos);
	double dx = _windowWidth / 2 - xpos;
	double dy = _windowHeight / 2 - ypos;
	if (fabs(dx) > _cursorInaccuracy || fabs(dy) > _cursorInaccuracy)
		_listener->cursorPositionChanged(dx, dy);
}
