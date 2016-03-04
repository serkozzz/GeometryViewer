#pragma once 
#include "IInputListener.h"


namespace gv
{ 
	namespace Engine
	{
		class Renderer;
		class WindowManager;
		class InputController;
		class ThreadManager;
		class RootEngineManager
		{
			static RootEngineManager* _rootEngineManagerInstance;
			RootEngineManager();
			WindowManager* _windowManager;
			InputController* _inputController;
			Renderer* _renderer;
			ThreadManager* _threadManager;
			bool _isInitialized;
			void startInSeparatedThread(int sizeX, int sizeY, IInputListener* InputListener);
		public: 
			static RootEngineManager* sharedRootEngineManager();

			void start(int sizeX, int sizeY, IInputListener* InputListener);
		};
	}
}