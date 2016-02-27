#pragma once 

#include <memory>
#include "../gvEngine/IInputListener.h"
#include "../gvModel/ICamera.h"

#include "ICameraMovingRealization.h"

namespace gv
{
	namespace Controller3D
	{
		class InputListener : public IInputListener
		{
			std::shared_ptr<ICameraMovingRealization> _cameraMovingRealization;


		public:
			InputListener(Model::ICamera* camera);
			virtual void keyPressed(gvKey key) const;
			virtual void cursorPositionChanged(double dx, double dy) const;
		};
	}
}