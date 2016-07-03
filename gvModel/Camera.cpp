#include "Camera.h"

using namespace gv::Model;

Camera::Camera(const std::string& name) : PlanElement(name)
{

}

void Camera::sendPropertyChanged(const std::string& propName) const
{
	this->propertyChanged(CameraPropChangedArgs(this, propName));
	PlanElement::sendPropertyChanged(propName);
}

void Camera::sendTryPropertyChanged(const void* newValue, const std::string& propName) const
{
	this->tryPropertyChanged(CameraTryPropChangedArgs(this, newValue, propName));
	PlanElement::sendTryPropertyChanged(newValue, propName);
}