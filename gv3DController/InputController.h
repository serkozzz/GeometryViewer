#pragma once 


#include "../gvEngine/IInputController.h"

namespace gv
{
	namespace Controller3D
	{
		class InputController : public IInputController
		{
		public:
			virtual void keyPressed(gvKey key);
		};
	}
}