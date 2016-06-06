#pragma once

#include <string>
#include <memory>
#include "ISceneNode.h"
#include "Material.h"


namespace gv
{
	namespace Engine
	{

		class SceneNode : public ISceneNode
		{
		protected:
			std::string _name;
			std::string _meshName;

			glm::vec3 _position;
			glm::vec3 _scale;
			glm::mat4 _rotationMatrix;

			glm::mat4 _transformMatrix;

			std::shared_ptr<Material> _material;

		public:
			SceneNode(const std::string& name);
			SceneNode(const std::string& name, const std::string& meshName);
			SceneNode(const std::string& name, const std::string& meshName, const glm::mat4& transform);

			void initialize(const std::string& name, 
				const std::string& meshName,
				const glm::mat4& transform, 
				std::shared_ptr<Material>& material);

			virtual std::string getName() const;

			virtual void setMesh(const std::string& meshName);
			virtual const std::string& getMesh();

			virtual glm::mat4 getTransformMatrix() const;
			virtual void setTransformMatrix(const glm::mat4& transform);

			virtual glm::vec3 getPosition() const;
			virtual void setPosition(const glm::vec3& position);

			virtual glm::vec3 getRotation() const;
			virtual void setRotation(const glm::vec3& rotation);

			virtual glm::vec3 getScale() const;
			virtual void setScale(const glm::vec3& scale);


			virtual std::shared_ptr<Material> getMaterial() const;
			virtual void setMaterial(const std::shared_ptr<Material>& material);
		};
	}
}