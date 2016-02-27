#include "CameraMover.h"

using namespace gv::Model;


CameraMover::CameraMover(mCamera* camera)
	: _camera(camera)
{
	_subscriptiomId = 
		(_camera->tryPropertyChanged += std::bind(&CameraMover::cameraTryPropertyChanged, this, std::placeholders::_1));
}

CameraMover::~CameraMover()
{
	_camera->tryPropertyChanged -= _subscriptiomId;
}


void CameraMover::cameraTryPropertyChanged(const CameraPropChangedArgs& arg)
{
	if (arg.propName == ICamera::namePropertyName)
	{
		const std::string* name = static_cast<const std::string*>(arg.newValue);
		_camera->setName(*name);
	}
	else if (arg.propName == ICamera::transformPropertyName)
	{
		const glm::mat4* transform = static_cast<const glm::mat4*>(arg.newValue);
		_camera->setTransform(*transform);
	}
	else if (arg.propName == ICamera::positionPropertyName)
	{
		const glm::vec3* newPosition = static_cast<const glm::vec3*>(arg.newValue);
		_camera->setPosition(*newPosition);
	}
}
