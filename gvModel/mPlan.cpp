#include "mPlan.h"

using namespace gv::Model;


void mPlan::AddPoint(std::shared_ptr<mPoint> p)
{
	_points.push_back(p);
	pointAdded(p);
}



void mPlan::RemovePoint(std::shared_ptr<mPoint> p)
{
	//_points.erase(std::remove(_points.begin(), _points.end(), p));
	_points.remove(p);
	pointRemoved(p);
}
