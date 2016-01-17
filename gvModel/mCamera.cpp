#include "mCamera.h"

using namespace gv::Model;


glm::mat4 mCamera::getTransform() const
{
	return _transform;
}

void mCamera::trySetTransform(const glm::mat4& newTransform)
{
	tryPropertyChanged(CameraPropChangedArgs(this, &newTransform, ICamera::transformPropertyName));
}

std::string mCamera::getName() const
{
	return _name;


}


void mCamera::trySetName(const std::string& newName)
{
	tryPropertyChanged(CameraPropChangedArgs(this, &newName, ICamera::namePropertyName));
}
