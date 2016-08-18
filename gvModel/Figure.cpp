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
	std::unique_ptr<Point> newPoint(new Point("point " + std::to_string(pointsNumber)));

	if (pointAfterInsertion == nullptr)
	{
		_points.push_back(std::move(newPoint));
		return _points.back().get();
	}
	auto it = _points.find(pointAfterInsertion);
	return (*_points.insert(it, std::move(newPoint))).get();
}


bool Figure::removePoint(const Point* point)
{
	_points.erase(_points.find(point));
	return true;
}