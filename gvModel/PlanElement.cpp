

#include "PlanElement.h"
#include <Transform.h>

using namespace gv::Model;

const std::string PlanElement::positionPropertyName = "position";
const std::string PlanElement::rotationPropertyName = "rotation";
const std::string PlanElement::scalePropertyName = "scale";
const std::string PlanElement::namePropertyName = "name";


PlanElement::PlanElement()
{
	_transform = std::make_shared<Transform>();
}


glm::vec3  PlanElement::PlanElement::getPosition() const
{
	return _transform->position;
}

void PlanElement::PlanElement::setPosition(const glm::vec3& newPosition)
{
	_transform->position = newPosition;
	propertyChanged(PlanElementPropChangedArgs(this, PlanElement::positionPropertyName));
}

void PlanElement::trySetPosition(const glm::vec3& newPosition) const
{
	tryPropertyChanged(PlanElementTryPropChangedArgs(this, &newPosition, PlanElement::positionPropertyName));
}

glm::vec3 PlanElement::getRotationEuler() const
{
	return _transform->rotationEuler;
}

void PlanElement::setRotationEuler(const glm::vec3& newRotation)
{
	_transform->rotationEuler = newRotation;
	propertyChanged(PlanElementPropChangedArgs(this, PlanElement::rotationPropertyName));
}

void PlanElement::trySetRotationEuler(const glm::vec3& newRotation) const
{
	tryPropertyChanged(PlanElementTryPropChangedArgs(this, &newRotation, PlanElement::rotationPropertyName));
}

glm::vec3  PlanElement::getScale() const
{
	return _transform->scale;
}

void PlanElement::setScale(const glm::vec3& newScale)
{
	_transform->scale = newScale;
	propertyChanged(PlanElementPropChangedArgs(this, PlanElement::scalePropertyName));
}

void PlanElement::trySetScale(const glm::vec3& newScale) const
{
	tryPropertyChanged(PlanElementTryPropChangedArgs(this, &newScale, PlanElement::scalePropertyName));
}

std::string PlanElement::getName() const
{
	return _name;
}

void PlanElement::setName(const std::string& newName)
{
	_name = newName;
	propertyChanged(PlanElementPropChangedArgs(this, PlanElement::namePropertyName));
}

void PlanElement::trySetName(const std::string& newName) const
{
	tryPropertyChanged(PlanElementTryPropChangedArgs(this, &newName, PlanElement::namePropertyName));
}
