#pragma once

#include "IPoint.h"

namespace gv
{
	namespace View
	{
		class vPoint : public IPoint
		{
			glm::vec3 _position;
			std::string _name;
			PrimitiveType _primitive;

		public:
			vPoint(const IPoint* p)
			{
				_name = p->getName();
				_position = p->getPosition();
				_primitive = p->getPrimitive();
			}

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
			}

			void trySetPosition(const glm::vec3& newPosition)
			{
			}

			const std::string& getName() const
			{
				return _name;
			}

			void setName(const std::string& newName)
			{
				_name = newName;
			}

			void trySetName(const std::string& newName)
			{
			}

			PrimitiveType getPrimitive() const
			{
				return _primitive;
			}

			void setPrimitive(const PrimitiveType& newPrimitive)
			{
				_primitive = newPrimitive;
			}

			void trySetPrimitive(const PrimitiveType& newPrimitive)
			{
			}
		};
	}
}