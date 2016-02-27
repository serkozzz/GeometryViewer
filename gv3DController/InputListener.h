#pragma once 


#include "../gvEngine/IInputListener.h"
#include "../gvModel/ICamera.h"

namespace gv
{
	namespace Controller3D
	{
		class InputListener : public IInputListener
		{
			const Model::ICamera* _camera;
			mutable float _horizontalAngle;
			mutable float _verticalAngle;

			glm::vec3 getDirection() const;
			glm::vec3 getRight() const;
			glm::mat4 getCameraTransform() const;
		public:
			InputListener(Model::ICamera* camera);
			virtual void keyPressed(gvKey key) const;
			virtual void cursorPositionChanged(double dx, double dy) const;
		};
	}
}