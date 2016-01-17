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

			virtual glm::mat4 getTransform() const = 0;
			virtual void trySetTransform(const glm::mat4& newTransform) = 0;

			virtual std::string getName() const = 0;
			virtual void trySetName(const std::string& newName) = 0;

			skb::EventHandler<CameraPropChangedArgs> propertyChanged;
		};
	}
}