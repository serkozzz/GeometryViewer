#pragma once

#include "glm/glm.hpp"
#include <memory>

namespace gv
{
	namespace Engine
	{
		class Material
		{
			glm::vec3 _color;
		public:
			Material(const glm::vec3& color);
			Material(float r, float g, float b);

			glm::vec3 getColor() const;
			void setColor(const glm::vec3& color);
			static std::shared_ptr<Material> createDefaultMaterial();
		};
	}
}