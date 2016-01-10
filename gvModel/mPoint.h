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

			const glm::vec3& getPosition() const
			{
				return _position;
			}

			void setPosition(const glm::vec3& newPosition)
			{
				_position = newPosition;
				propertyChanged(PointPropChangedArgs(this, &_position, IPoint::positionPropertyName));
			}

			void trySetPosition(const glm::vec3& newPosition)
			{
				tryPropertyChanged(PointPropChangedArgs(this, &_position, IPoint::positionPropertyName));
			}

			const std::string& getName() const
			{
				return _name;
			}

			void setName(const std::string& newName)
			{
				_name = newName;
				propertyChanged(PointPropChangedArgs(this, &_name, IPoint::namePropertyName));
			}

			void trySetName(const std::string& newName)
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

			void trySetPrimitive(const PrimitiveType& newPrimitive)
			{
				tryPropertyChanged(PointPropChangedArgs(this, &_primitive, IPoint::primitivePropertyName));
			}

			skb::EventHandler<PointPropChangedArgs> propertyChanged;
			skb::EventHandler<PointPropChangedArgs> tryPropertyChanged;
		};

	}


}