#pragma once

#include "IRenderer.h"

namespace gv
{
	namespace Engine
	{
		class WindowManager;
	
		//TODO exclude glfw dependency from this class
		class Renderer : public IRenderer
		{
			WindowManager* _windowManager;
		public: 
			Renderer(WindowManager* windowManager);
			virtual void renderFrame(float TimeFromLastFrameMs);
			virtual ~Renderer();
		};
	}
}