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
		static const std::string rotationPropertyName;
		static const std::string scalePropertyName;
		static const std::string namePropertyName;
		static const std::string primitivePropertyName;
		

		virtual glm::vec3 getPosition() const = 0;
		virtual void trySetPosition(const glm::vec3& newPosition) const = 0;

		
		virtual glm::vec3 getRotation() const = 0;
		virtual void trySetRotation(const glm::vec3& newRotation) const = 0;

		virtual glm::vec3 getScale() const = 0;
		virtual void trySetScale(const glm::vec3& newScale) const = 0;

		virtual std::string getName() const = 0;
		virtual void trySetName(const std::string& newName) const = 0;

		virtual PrimitiveType getPrimitive() const = 0;
		virtual void trySetPrimitive(const PrimitiveType& newPrimitive) const = 0;

		mutable skb::EventHandler<PointPropChangedArgs> propertyChanged;
	};



}