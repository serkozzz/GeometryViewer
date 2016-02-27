#pragma once

#include "ICamera.h"

namespace gv
{
	namespace Model
	{
		class mCamera : public ICamera
		{
			glm::mat4 _transform;
			std::string _name;
		public:

			mCamera();

			virtual glm::mat4 getTransform() const;
			virtual void trySetTransform(const glm::mat4& newTransform) const;
			void setTransform(const glm::mat4& newTransform);

			virtual glm::vec3 getPosition() const;
			virtual void setPosition(const glm::vec3& newPosition);
			virtual void trySetPosition(const glm::vec3& newPosition) const;

			//TODO
			//
			//virtual glm::vec3 getRotation() const = 0;
			//virtual void setRotation(const glm::vec3& newRotation) = 0;
			//virtual void trySetRotation(const glm::vec3& newRotation) const = 0;

			virtual std::string getName() const;
			virtual void trySetName(const std::string& newName) const;
			void setName(const std::string& newName);

			skb::EventHandler<const CameraPropChangedArgs&> tryPropertyChanged;
		};
	}
}