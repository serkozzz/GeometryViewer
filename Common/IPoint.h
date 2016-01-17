#pragma once


#include <string>
#include "glm/glm.hpp"
#include "common.h"
#include "EventHandler.h"




namespace gv
{
	class IPoint;
	typedef skb::PropertyChangedArgs<IPoint> PointPropChangedArgs;

	class IPoint
	{
	public:

		static const std::string positionPropertyName;
		static const std::string namePropertyName;
		static const std::string primitivePropertyName;


		virtual glm::vec3 getPosition() const = 0;
		virtual void trySetPosition(const glm::vec3& newPosition) = 0;

		virtual std::string getName() const = 0;
		virtual void trySetName(const std::string& newName) = 0;

		virtual PrimitiveType getPrimitive() const = 0;
		virtual void trySetPrimitive(const PrimitiveType& newPrimitive) = 0;

		skb::EventHandler<PointPropChangedArgs> propertyChanged;
	};



}