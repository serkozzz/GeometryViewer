#pragma once
#include "dllexport.h"
#include "glm/glm.hpp"

namespace gv
{ 
	namespace Engine
	{
		class ISceneNode
		{
		public:
			virtual void setMesh(const std::string& meshName) = 0;

			virtual glm::mat4 getTransformMatrix() = 0;
			virtual void setTransformMatrix(const glm::mat4& transform) = 0;

			virtual glm::vec3 getPosition() = 0;
			virtual void setPosition(const glm::vec3& position) = 0;

			virtual glm::vec3 getScale() = 0;
			virtual void setScale(const glm::vec3& scale) = 0;

			//TO DO rotations methods
		};
	}
}