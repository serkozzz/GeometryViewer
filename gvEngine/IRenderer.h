#pragma once

namespace gv
{
	namespace Engine
	{
		class IRenderer
		{
		public: 
			virtual void renderFrame(float TimeFromLastFrameMs) = 0;
			virtual ~IRenderer()
			{
			}
		};
	}
}