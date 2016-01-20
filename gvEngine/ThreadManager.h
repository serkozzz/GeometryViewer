#pragma once 

#include <memory>
#include "IRenderer.h"
#include "IInputController.h"


namespace gv
{
	namespace Engine
	{
		
		class ThreadManager
		{
			std::shared_ptr<IRenderer> _renderer;
			std::shared_ptr<IInputController> _inputController;			

		public:
			ThreadManager(std::shared_ptr<IRenderer> renderer, std::shared_ptr<IInputController> _inputController);

		};
	}
}