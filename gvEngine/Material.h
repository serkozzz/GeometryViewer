#pragma once

#include "glm\vec3.hpp"

namespace gv
{
	namespace Engine
	{
		class Material
		{
			glm::vec3 _color;
		public:
			Material(glm::vec3);
			glm::vec3 getColor() const;
			void setColor(const glm::vec3& color);
		};
	}
}