
#include "Material.h"

namespace gv
{
	namespace Engine
	{

		Material::Material(const glm::vec3& color) : _color(color)
		{

		}

		Material::Material(float r, float g, float b)
		{
			_color = glm::vec3(r, g, b);
		}


		glm::vec3 Material::getColor() const
		{
			return _color;
		}


		void Material::setColor(const glm::vec3& color)
		{
			_color = color;
		}

		std::shared_ptr<Material> Material::createDefaultMaterial()
		{
			return std::make_shared<Material>(glm::vec3(1, 1, 0));
		}
	}
}