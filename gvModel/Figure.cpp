#include "Figure.h"

using namespace gv::Model;

const std::list<Point>* Figure::getPoints() const
{
	return &_points;
}


//std::list<Point>* Figure::getPoints()
//{
//	return &_points;
//}


void Figure::sendPropertyChanged(const std::string& propName) const
{
	this->propertyChanged(FigurePropChangedArgs(this, propName));
	PlanElement::sendPropertyChanged(propName);
}

void Figure::sendTryPropertyChanged(const void* newValue, const std::string& propName) const
{
	this->tryPropertyChanged(FigureTryPropChangedArgs(this, newValue, propName));
	PlanElement::sendTryPropertyChanged(newValue, propName);
}