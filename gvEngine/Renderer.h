#pragma once

#include "IRenderer.h"
#include "Camera.h"

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
			virtual void renderFrame(float timeFromLastFrameMs);
			virtual ~Renderer();
		};
	}
}