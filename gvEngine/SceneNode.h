#pragma once

#include <string>
#include "ISceneNode.h"

namespace gv
{
	namespace Engine
	{
		class SceneNode : public ISceneNode
		{
		protected:
			std::string _name;
			glm::mat4 _transformMatrix;

		public:
			SceneNode(const std::string& name);

			virtual std::string getName() const;

			virtual void setMesh(const std::string& meshName);

			virtual glm::mat4 getTransformMatrix() const;
			virtual void setTransformMatrix(const glm::mat4& transform);

			virtual glm::vec3 getPosition() const;
			virtual void setPosition(const glm::vec3& position);

			virtual glm::vec3 getScale() const;
			virtual void setScale(const glm::vec3& scale);
		};
	}
}