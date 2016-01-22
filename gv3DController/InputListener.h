#pragma once 


#include "../gvEngine/IInputListener.h"

namespace gv
{
	namespace Controller3D
	{
		class InputListener : public IInputListener
		{
		public:
			virtual void keyPressed(gvKey key) const;
		};
	}
}