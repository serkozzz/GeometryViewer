#include "PlanManager.h"
#include "mPlan.h"

using namespace gv;
using namespace gv::Model;

PlanManager::PlanManager()
{
	_plan = new mPlan();
	_cameraMover.reset(new CameraMover(_plan->getmCamera()));
}

PlanManager::~PlanManager()
{
	_cameraMover.reset();
	if (_plan)
		delete _plan;
}

IPlan* PlanManager::getPlan()
{
	return _plan;
}


void PlanManager::tryAddPoint(const std::shared_ptr<IPoint>& point)
{
	mPoint p(point.get());
	auto pPtr = std::make_shared<mPoint>(p);
	_plan->AddPoint(pPtr);
	_subscriptions[pPtr] = 
		(pPtr->tryPropertyChanged += std::bind(&PlanManager::onTryPointPropChanged, this, std::placeholders::_1));
}

void PlanManager::tryRemovePoint(const std::shared_ptr<IPoint>& point)
{

	if (!_plan->isPointExist(point))
	{
		throw std::exception("Attemption to delete point that is abscent in the plan");
	}

	point->propertyChanged -= _subscriptions[point];
	_subscriptions.erase(point);
	auto mp = std::dynamic_pointer_cast<mPoint>(point);
	_plan->RemovePoint(mp);
}

void PlanManager::onTryPointPropChanged(PointPropChangedArgs args)
{
	auto pPtr = std::shared_ptr<const IPoint>(args.sender);
	if (!_plan->isPointExist(pPtr))
	{
		throw std::exception("Attemption to change point property for point that is abscent in the plan");
	}
	auto& points = _plan->getPoints();
	auto it = std::find(points.begin(), points.end(), pPtr);

	if (args.propName == IPoint::namePropertyName)
	{
		const std::string* newName = static_cast<const std::string*>(args.newValue);
		(*it)->setName(*newName);
	}
	else if (args.propName == IPoint::positionPropertyName)
	{
		const glm::vec3* newPos = static_cast<const glm::vec3*>(args.newValue);
		(*it)->setPosition(*newPos);
	}
	else if (args.propName == IPoint::primitivePropertyName)
	{
		const PrimitiveType* newPrimitiveType = static_cast<const PrimitiveType*>(args.newValue);
		(*it)->trySetPrimitive(*newPrimitiveType);
	}
}