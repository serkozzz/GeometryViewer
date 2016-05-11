
#include "Material.h"

using namespace gv::Engine;


Material::Material(glm::vec3 color) : _color(color)
{

}


glm::vec3 Material::getColor() const
{
	return _color;
}


void Material::setColor(const glm::vec3& color)
{
	_color = color;
}