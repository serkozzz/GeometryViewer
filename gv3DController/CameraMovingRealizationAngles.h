#pragma once 


#include "ICameraMovingRealization.h"

namespace gv
{
	namespace Controller3D
	{
		class CameraMovingRealizationAngles : public ICameraMovingRealization
		{
			const Model::ICamera* _camera;
			float _horizontalAngle;
			float _verticalAngle;

			glm::vec3 getDirection() const;
			glm::vec3 getRight() const;
			glm::mat4 getCameraTransform() const;
		public:
			virtual void setCamera(Model::ICamera* camera);
			virtual void moveCamera(float forward, float right);
			virtual void rotateCamera(float dx, float dy);
		};
	}
}