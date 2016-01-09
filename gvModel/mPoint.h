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
				tryPropertyChanged(skb::TryPropertyChangeArgs(IPoint::positionPropertyName, &newPosition));
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
				tryPropertyChanged(skb::TryPropertyChangeArgs(IPoint::namePropertyName, &newName));
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
				tryPropertyChanged(skb::TryPropertyChangeArgs(IPoint::primitivePropertyName, &newPrimitive));
			}

			skb::EventHandler<PointPropChangedArgs> propertyChanged;
			skb::EventHandler<skb::TryPropertyChangeArgs> tryPropertyChanged;
		};

	}


}