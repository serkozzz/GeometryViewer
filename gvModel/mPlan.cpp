#include "mPlan.h"

using namespace gv::Model;
using namespace gv;

ICamera* mPlan::getCamera()
{
	return &_camera;
}


void mPlan::AddPoint(const std::shared_ptr<mPoint>& p)
{
	_points.push_back(p);
	pointAdded(p);

}



void mPlan::RemovePoint(const std::shared_ptr<mPoint>& p)
{
	//_points.erase(std::remove(_points.begin(), _points.end(), p));
	_points.remove(p);
	pointRemoved(p);
}


const std::list<std::shared_ptr<mPoint> >& mPlan::getPoints() const
{
	return _points;
}


bool mPlan::isPointExist(const std::shared_ptr<const IPoint>& p) const
{
	auto it = std::find(_points.begin(), _points.end(), p);
	return (it == _points.end()) ? false : true;

}
