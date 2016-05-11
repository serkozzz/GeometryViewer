#pragma once

#include <string>
#include "glm/glm.hpp"

namespace gv
{ 
	namespace Engine
	{
		class Material;
		class ISceneNode
		{
		public:
			virtual std::string getName() const = 0;

			virtual void setMesh(const std::string& meshName) = 0;
			virtual const std::string& getMesh() = 0;

			virtual glm::mat4 getTransformMatrix() const = 0;
			virtual void setTransformMatrix(const glm::mat4& transform) = 0;

			virtual glm::vec3 getPosition() const = 0;
			virtual void setPosition(const glm::vec3& position) = 0;

			virtual glm::vec3 getRotation() const = 0;
			virtual void setRotation(const glm::vec3& rotation) = 0;

			virtual glm::vec3 getScale() const = 0;
			virtual void setScale(const glm::vec3& scale) = 0;


			virtual std::shared_ptr<Material> getMaterial() const;
			virtual void setMaterial(const std::shared_ptr<Material> material);

			//TO DO rotations methods
		};
	}
}