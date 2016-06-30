#include "CameraMover.h"

using namespace gv::Model;


CameraMover::CameraMover(Camera* camera)
	: _camera(camera)
{
	_subscriptiomId = 
		(_camera->tryPropertyChanged += std::bind(&CameraMover::cameraTryPropertyChanged, this, std::placeholders::_1));
}

CameraMover::~CameraMover()
{
	_camera->tryPropertyChanged -= _subscriptiomId;
}


void CameraMover::cameraTryPropertyChanged(const CameraTryPropChangedArgs& arg)
{
	if (arg.propName == Camera::namePropertyName)
	{
		const std::string* name = static_cast<const std::string*>(arg.newValue);
		_camera->setName(*name);
	}
	else if (arg.propName == Camera::positionPropertyName)
	{
		const glm::vec3* newPosition = static_cast<const glm::vec3*>(arg.newValue);
		_camera->setPosition(*newPosition);
	}
	else if (arg.propName == Camera::rotationPropertyName)
	{
		const glm::vec3* newRotation = static_cast<const glm::vec3*>(arg.newValue);
		_camera->setRotationEuler(*newRotation);
	}
	//else if (arg.propName == Camera::scalePropertyName)
	//{
	//	const glm::vec3* newScale = static_cast<const glm::vec3*>(arg.newValue);
	//	_camera->setRotationEuler(*newScale);
	//}
}
