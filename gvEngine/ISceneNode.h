#pragma once

namespace gv
{ 
	namespace Engine
	{
		class ISceneNode
		{
		public:
			virtual glm::mat4 getTransformMatrix() = 0;
			virtual void setTransformMatrix(const glm::mat4& transform) = 0;

			virtual glm::vec3 getPosition() = 0;
			virtual void setPosition(glm::vec3& position) = 0;

			virtual glm::vec3 getScale() = 0;
			virtual void setScale(glm::vec3& scale) = 0;

			//TO DO rotations methods
		};
	}
}