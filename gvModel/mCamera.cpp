#include <glm/gtc/matrix_transform.hpp>

#include "mCamera.h"

using namespace gv::Model;

mCamera::mCamera()
{
	_transform = glm::mat4(1.0f);
}


glm::mat4 mCamera::getTransform() const
{
	return _transform;
}


void mCamera::setTransform(const glm::mat4& newTransform)
{
	_transform = newTransform;
	propertyChanged(CameraPropChangedArgs(this, &newTransform, ICamera::transformPropertyName));
}



void mCamera::trySetTransform(const glm::mat4& newTransform) const
{
	tryPropertyChanged(CameraPropChangedArgs(this, &newTransform, ICamera::transformPropertyName));
}


glm::vec3 mCamera::getPosition() const
{
	return glm::vec3(_transform[3].x, _transform[3].y, _transform[3].z);
}


void mCamera::setPosition(const glm::vec3& newPosition)
{
	_transform[3] = glm::vec4(newPosition, 1.0f);
	propertyChanged(CameraPropChangedArgs(this, &newPosition, ICamera::positionPropertyName));
}

void mCamera::trySetPosition(const glm::vec3& newPosition) const
{
	tryPropertyChanged(CameraPropChangedArgs(this, &newPosition, ICamera::positionPropertyName));
}



std::string mCamera::getName() const
{
	return _name;
}

void  mCamera::setName(const std::string& newName)
{
	_name = newName;
	propertyChanged(CameraPropChangedArgs(this, &newName, ICamera::namePropertyName));
}

void mCamera::trySetName(const std::string& newName) const
{
	tryPropertyChanged(CameraPropChangedArgs(this, &newName, ICamera::namePropertyName));
}
