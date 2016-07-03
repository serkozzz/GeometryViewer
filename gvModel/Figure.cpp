#include "Figure.h"

using namespace gv::Model;


Figure::Figure(const std::string& name) : PlanElement(name)
{
}


const PointsCollection* Figure::getPoints() const
{
	return &_points;
}

PointsCollection* Figure::getPoints()
{
	return &_points;
}

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


const Point* Figure::addNewPoint(const Point* pointAfterInsertion)
{
	size_t pointsNumber = _points.size();
	Point newPoint("point " + std::to_string(pointsNumber));
	return _points.insert(std::move(newPoint), pointAfterInsertion);
}


bool Figure::removePoint(const Point* point)
{
	return _points.remove(point);
}