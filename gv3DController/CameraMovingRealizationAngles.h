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

			glm::vec3 calculateDirection() const;
			glm::vec3 calculateRight() const;
			glm::mat4 calculateCameraTransform() const;
		public:
			virtual void setCamera(Model::ICamera* camera);
			virtual void moveCamera(float right, float forward);
			virtual void rotateCamera(float dx, float dy);
		};
	}
}