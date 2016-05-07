
#include <glfw3.h>
#include <math.h>

#include "InputController.h"

using namespace gv;
using namespace gv::Engine;

InputController::InputController(GLFWwindow* window, const IInputListener* listener) 
	: _window(window), _listener(listener), _cursorInaccuracy(0.00001), isDisabled(false)
{
	glfwGetWindowSize(_window, &_windowWidth, &_windowHeight);
	glfwGetCursorPos(_window, &_cursorX, &_cursorY);
}

InputController::~InputController()
{
}

void InputController::checkInput()
{
	double xpos, ypos;
	glfwGetCursorPos(_window, &xpos, &ypos);

	if (glfwGetKey(_window, GLFW_KEY_LEFT_CONTROL ) == GLFW_PRESS){
		isDisabled = !isDisabled;
		if (!isDisabled)
		{
			_cursorX = xpos;
			_cursorY = ypos;
		}
	}

	if (isDisabled)
		return;

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


	double dx = _cursorX - xpos;
	double dy = _cursorY - ypos;
	if (fabs(dx) > _cursorInaccuracy || fabs(dy) > _cursorInaccuracy)
	{
		_listener->cursorPositionChanged(dx, dy);
		_cursorX = xpos;
		_cursorY = ypos;
	}
}
