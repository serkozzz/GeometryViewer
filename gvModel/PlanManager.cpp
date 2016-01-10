#include "PlanManager.h"

using namespace gv;
using namespace gv::Model;

IPlan* PlanManager::getPlan()
{
	return &_plan;
}

void PlanManager::tryAddPoint(const std::shared_ptr<IPoint>& point)
{
	mPoint p(point.get());
	_plan.AddPoint(std::make_shared<mPoint>(p));
}

void PlanManager::tryRemovePoint(const std::shared_ptr<IPoint>& point)
{

}