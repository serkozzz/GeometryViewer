#pragma once

#include "IInputController.h"
#include "IInputListener.h"

struct GLFWwindow;


namespace gv
{
	namespace Engine
	{


		class InputController : public IInputController
		{
			const float _cursorInaccuracy;
			int _windowWidth;
			int _windowHeight;
			GLFWwindow*  _window;
			const IInputListener* _listener;
		public:
			InputController(GLFWwindow* _window, const IInputListener* listener);
			virtual void checkInput();
			virtual ~InputController();
		};
	}
}