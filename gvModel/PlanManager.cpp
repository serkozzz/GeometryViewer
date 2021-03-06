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


void PlanManager::createNewPoint()
{
	static int pointsCount = 0;

	mPoint p("point" + std::to_string(pointsCount), 
		glm::vec3(0, 0, 0),
		PrimitiveType::cubePrimitiveType);
	pointsCount++;

	auto pPtr = std::make_shared<mPoint>(p);

	_plan->AddPoint(pPtr);
	_subscriptions[pPtr] = 
		(pPtr->tryPropertyChanged += std::bind(&PlanManager::onTryPointPropChanged, this, std::placeholders::_1));

}

void PlanManager::removePoint(const IPoint* point)
{

	auto mpoint = _plan->getPointByPointer(point);

	if (mpoint == nullptr)
	{
		throw std::exception("Attemption to delete point that is abscent in the plan");
	}

	mpoint->propertyChanged -= _subscriptions[mpoint];
	_subscriptions.erase(mpoint);
	_plan->RemovePoint(mpoint);
}

void PlanManager::onTryPointPropChanged(PointPropChangedArgs args)
{
	auto pPtr = static_cast<const IPoint*>(args.sender);
	std::shared_ptr<mPoint> mpoint = _plan->getPointByPointer(pPtr);

	if (mpoint == nullptr)
	{
		throw std::exception("Attemption to change point property for point that is abscent in the plan");
	}

	if (args.propName == IPoint::namePropertyName)
	{
		const std::string* newName = static_cast<const std::string*>(args.newValue);
		mpoint->setName(*newName);
	}
	else if (args.propName == IPoint::positionPropertyName)
	{
		const glm::vec3* newPos = static_cast<const glm::vec3*>(args.newValue);
		mpoint->setPosition(*newPos);
	}
	else if (args.propName == IPoint::rotationPropertyName)
	{
		const glm::vec3* newRotation = static_cast<const glm::vec3*>(args.newValue);
		mpoint->setRotation(*newRotation);
	}
	else if (args.propName == IPoint::scalePropertyName)
	{
		const glm::vec3* newScale = static_cast<const glm::vec3*>(args.newValue);
		mpoint->setScale(*newScale);
	}
	else if (args.propName == IPoint::primitivePropertyName)
	{
		const PrimitiveType* newPrimitiveType = static_cast<const PrimitiveType*>(args.newValue);
		mpoint->trySetPrimitive(*newPrimitiveType);
	}
}