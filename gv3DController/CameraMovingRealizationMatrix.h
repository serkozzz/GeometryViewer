#pragma once 


#include "ICameraMovingRealization.h"

namespace gv
{
	namespace Controller3D
	{
		class CameraMovingRealizationMatrix : public ICameraMovingRealization
		{
			const Model::ICamera* _camera;
		public:
			virtual void setCamera(Model::ICamera* camera);
			virtual void moveCamera(float forward, float right);
			virtual void rotateCamera(float dx, float dy);
		};
	}
}