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
			GLFWwindow*  _window;
			const IInputListener* _listener;
		public:
			InputController(const IInputListener* listener);
			virtual void checkInput();
			virtual ~InputController();
		};
	}
}