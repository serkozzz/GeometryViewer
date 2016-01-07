#pragma once

#include "glm/glm.hpp"
#include "common.h"
#include "EventHandler.h"
#include <string>

namespace gv
{
	namespace gvView
	{
		class vPoint
		{
			glm::vec3 _position;
			std::string _name;
			PrimitiveType _primitive;

		public:

			static std::string positionPropertyName;
			static std::string namePropertyName;
			static std::string primitivePropertyName;

			vPoint(std::string name, glm::vec3 position, PrimitiveType primitive)
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
				propertyChanged(vPoint::positionPropertyName);
			}

			void trySetPosition(const glm::vec3& newPosition)
			{
				tryPropertyChanged(skb::TryPropertyChangeArgs(vPoint::positionPropertyName, &newPosition));
			}

			const std::string& getName() const
			{
				return _name;
			}

			void setName(const std::string& newName)
			{
				_name = newName;
				propertyChanged(vPoint::namePropertyName);
			}

			void trySetName(const std::string& newName)
			{
				tryPropertyChanged(skb::TryPropertyChangeArgs(vPoint::namePropertyName, &newName));
			}

			PrimitiveType getPrimitive() const
			{
				return _primitive;
			}

			void setPrimitive(const PrimitiveType& newPrimitive)
			{
				_primitive = newPrimitive;
				propertyChanged(vPoint::primitivePropertyName);
			}

			void trySetPrimitive(const PrimitiveType& newPrimitive)
			{
				tryPropertyChanged(skb::TryPropertyChangeArgs(vPoint::primitivePropertyName, &newPrimitive));
			}

			skb::EventHandler<std::string> propertyChanged;
			skb::EventHandler<skb::TryPropertyChangeArgs> tryPropertyChanged;
		};



		std::string vPoint::positionPropertyName = "position";
		std::string vPoint::namePropertyName = "name";
		std::string vPoint::primitivePropertyName = "primitive";
	}


}