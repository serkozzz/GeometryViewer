#pragma once

#include "../gvModel/ICamera.h"

namespace gv
{
	namespace Controller3D
	{
		class ICameraMovingRealization
		{
		public:
			virtual void setCamera(gv::Model::ICamera* camera) = 0;
			virtual void moveCamera(float right, float forward) = 0;
			virtual void rotateCamera(float dx, float dy) = 0;
		};
	}
}