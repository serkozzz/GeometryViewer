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
			std::string _meshName;

			glm::mat4 _transformMatrix;

		public:
			SceneNode(const std::string& name);
			SceneNode(const std::string& name, const std::string& meshName);
			SceneNode(const std::string& name, const std::string& meshName, const glm::mat4& transform);

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