#pragma once

#include "Camera.h"

namespace gv
{
	namespace Engine
	{
		class DoNothingCamera : public Camera
		{
		public:
			DoNothingCamera(const std::string& name, float aspect);

			virtual glm::mat4 getViewMatrix() const;
			virtual glm::mat4 getProjectMatrix() const;
			virtual glm::mat4 getViewProjectMatrix() const;
		};
	}
}