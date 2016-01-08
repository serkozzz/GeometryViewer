#pragma once

#include "glm/glm.hpp"
#include "common.h"
#include "EventHandler.h"
#include <string>

namespace gv
{
		class IPoint
		{
		public:

			static std::string positionPropertyName;
			static std::string namePropertyName;
			static std::string primitivePropertyName;

			virtual const glm::vec3& getPosition() const = 0;
			virtual void trySetPosition(const glm::vec3& newPosition) = 0;
			
			virtual const std::string& getName() const = 0;
			virtual void trySetName(const std::string& newName) = 0;

			virtual PrimitiveType getPrimitive() const = 0;
			virtual void trySetPrimitive(const PrimitiveType& newPrimitive) = 0;

			skb::EventHandler<std::string> propertyChanged;
		};

		std::string IPoint::positionPropertyName = "position";
		std::string IPoint::namePropertyName = "name";
		std::string IPoint::primitivePropertyName = "primitive";
}