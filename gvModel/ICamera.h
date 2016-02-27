#pragma once 

#include <string>
#include "EventHandler.h"
#include "common.h"
#include "glm/glm.hpp"


namespace gv
{
	namespace Model
	{
		class ICamera;
		typedef skb::PropertyChangedArgs<ICamera> CameraPropChangedArgs;
		class ICamera
		{
		public:

			static const std::string transformPropertyName;
			static const std::string namePropertyName;
			static const std::string positionPropertyName;

			virtual glm::mat4 getTransform() const = 0;
			virtual void trySetTransform(const glm::mat4& newTransform) const = 0;

			virtual glm::vec3 getPosition() const = 0;
			virtual void trySetPosition(const glm::vec3& newPosition) const = 0;

			//TODO
			//virtual glm::vec3 getRotation() const = 0;
			//virtual void trySetRotation(const glm::vec3& newRotation) const = 0;


			virtual std::string getName() const = 0;
			virtual void trySetName(const std::string& newName) const = 0;

			skb::EventHandler<const CameraPropChangedArgs&> propertyChanged;
		};
	}
}