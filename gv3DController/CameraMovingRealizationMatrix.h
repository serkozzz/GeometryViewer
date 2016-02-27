#pragma once 


#include "ICameraMovingRealization.h"

namespace gv
{
	namespace Controller3D
	{
		class CameraMovingRealizationMatrix : public ICameraMovingRealization
		{
		public:
			virtual void setCamera(Model::ICamera* camera);
			virtual void moveCamera(float forward, float right);
			virtual void rotateCamera(float dx, float dy);
		};
	}
}