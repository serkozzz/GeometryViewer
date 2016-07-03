
#include "Point.h"


using namespace gv;
using namespace gv::Model;

const std::string Point::primitivePropertyName = "primitive";



Point::Point(const std::string& name) : PlanElement(name)
{

}



PrimitiveType Point::getPrimitive() const
{
	return _primitive;
}

void Point::setPrimitive(const PrimitiveType& newPrimitive)
{
	_primitive = newPrimitive;
	sendPropertyChanged(Point::primitivePropertyName);
}

void Point::trySetPrimitive(const PrimitiveType& newPrimitive) const
{
	sendTryPropertyChanged(&_primitive, Point::primitivePropertyName);
}



void Point::sendPropertyChanged(const std::string& propName) const
{
	this->propertyChanged(PointPropChangedArgs(this, propName));
	PlanElement::sendPropertyChanged(propName);
}

void Point::sendTryPropertyChanged(const void* newValue, const std::string& propName) const
{
	this->tryPropertyChanged(PointTryPropChangedArgs(this, newValue, propName));
	PlanElement::sendTryPropertyChanged(newValue, propName);
}