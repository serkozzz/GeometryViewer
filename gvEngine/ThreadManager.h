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

			std::chrono::duration<double, std::milli> _inputCheckInterval;
			std::chrono::duration<double, std::milli> _renderLoopInterval;
			std::chrono::system_clock::time_point _lastRenderTime;


		public:
			///all intervals in ms
			ThreadManager(std::shared_ptr<IRenderer> renderer, 
				std::shared_ptr<IInputController> inputController, 
				float inputCheckInterval,
				float renderLoopInterval);
			void start();
		};
	}
}