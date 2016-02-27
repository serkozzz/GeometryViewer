#pragma once
#include "dllexport.h"
#include "SceneNode.h"

namespace gv
{
	namespace Engine
	{
		class GVAPI Camera : public SceneNode
		{
			float _fov;
			float _aspect;
			float _nearClipDistance;
			float _farClipDistance;
			glm::mat4 _projectionMatrix;
		public:
			Camera(const std::string& name, float aspect);
			void setFOV(float fov);
			glm::mat4 getViewMatrix() const;
			glm::mat4 getProjectMatrix() const;
			glm::mat4 getViewProjectMatrix() const;
		};
	}
}