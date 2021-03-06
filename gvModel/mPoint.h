#pragma once

#include <string>
#include "glm/glm.hpp"

#include "common.h"
#include "EventHandler.h"
#include "IPoint.h"

namespace gv
{
	namespace Model 
	{
		class mPoint : public IPoint
		{
			glm::vec3 _position;
			glm::vec3 _rotation;
			glm::vec3 _scale;
			std::string _name;
			PrimitiveType _primitive;

		public:

			mPoint(const IPoint* p)
			{
				_name = p->getName();
				_position = p->getPosition();
				_primitive = p->getPrimitive();
			}

			mPoint(std::string name, glm::vec3 position, PrimitiveType primitive)
				: _name(name), _position(position), _primitive(primitive)
			{

			}

			glm::vec3 getPosition() const
			{
				return _position;
			}

			void setPosition(const glm::vec3& newPosition)
			{
				_position = newPosition;
				propertyChanged(PointPropChangedArgs(this, &newPosition, IPoint::positionPropertyName));
			}

			void trySetPosition(const glm::vec3& newPosition) const
			{
				tryPropertyChanged(PointPropChangedArgs(this, &newPosition, IPoint::positionPropertyName));
			}

			glm::vec3 getRotation() const
			{
				return _rotation;
			}

			void setRotation(const glm::vec3& newRotation)
			{
				_rotation = newRotation;
				propertyChanged(PointPropChangedArgs(this, &newRotation, IPoint::rotationPropertyName));
			}

			void trySetRotation(const glm::vec3& newRotation) const
			{
				tryPropertyChanged(PointPropChangedArgs(this, &newRotation, IPoint::rotationPropertyName));
			}

			glm::vec3 getScale() const
			{
				return _scale;
			}

			void setScale(const glm::vec3& newScale)
			{
				_scale = newScale;
				propertyChanged(PointPropChangedArgs(this, &newScale, IPoint::scalePropertyName));
			}

			void trySetScale(const glm::vec3& newScale) const
			{
				tryPropertyChanged(PointPropChangedArgs(this, &newScale, IPoint::scalePropertyName));
			}

			std::string getName() const
			{
				return _name;
			}

			void setName(const std::string& newName)
			{
				_name = newName;
				propertyChanged(PointPropChangedArgs(this, &_name, IPoint::namePropertyName));
			}

			void trySetName(const std::string& newName) const
			{
				tryPropertyChanged(PointPropChangedArgs(this, &newName, IPoint::namePropertyName));
			}

			PrimitiveType getPrimitive() const
			{
				return _primitive;
			}

			void setPrimitive(const PrimitiveType& newPrimitive)
			{
				_primitive = newPrimitive;
				propertyChanged(PointPropChangedArgs(this, &_primitive, IPoint::primitivePropertyName));
			}

			void trySetPrimitive(const PrimitiveType& newPrimitive) const
			{
				tryPropertyChanged(PointPropChangedArgs(this, &_primitive, IPoint::primitivePropertyName));
			}

			//skb::EventHandler<PointPropChangedArgs> propertyChanged;
			skb::EventHandler<PointPropChangedArgs> tryPropertyChanged;
		};

	}


}