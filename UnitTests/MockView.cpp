#include "stdafx.h"

#include "MockView.h"

using namespace gv;
using namespace gv::View;

namespace UnitTests
{
	void MockView::pointAdded(const std::shared_ptr<IPoint>& p)
	{
		_vPoints[p] = std::make_shared<vPoint>(vPoint(p.get()));
	}


	void MockView::pointRemoved(const std::shared_ptr<gv::IPoint>& p)
	{
		auto it = _vPoints.find(p);
		if (it == _vPoints.end())
		{
			throw std::exception("MockView: Attemption to delete point that is abscent in the view");
		}
		_vPoints.erase(it->first);
	}


	void MockView::pointSelected(const std::shared_ptr<gv::IPoint>& p)
	{

	}


	void MockView::pointUnSelected(const std::shared_ptr<gv::IPoint>& p)
	{

	}

	//void onTryPointPropChanged(gv::PointPropChangedArgs args)
	//{
	//	auto pPtr = std::shared_ptr<const IPoint>(args.sender);
	//	if (!_plan.isPointExist(pPtr))
	//	{
	//		throw std::exception("Attemption to change point property for point that is abscent in the plan");
	//	}
	//	auto& points = _plan.getPoints();
	//	auto it = std::find(points.begin(), points.end(), pPtr);

	//	if (args.propName == IPoint::namePropertyName)
	//	{
	//		const std::string* newName = static_cast<const std::string*>(args.newValue);
	//		(*it)->setName(*newName);
	//	}
	//	else if (args.propName == IPoint::positionPropertyName)
	//	{
	//		const glm::vec3* newPos = static_cast<const glm::vec3*>(args.newValue);
	//		(*it)->setPosition(*newPos);
	//	}
	//	else if (args.propName == IPoint::primitivePropertyName)
	//	{
	//		const PrimitiveType* newPrimitiveType = static_cast<const PrimitiveType*>(args.newValue);
	//		(*it)->trySetPrimitive(*newPrimitiveType);
	//	}
	//}



	void MockView::emulateAddPointClick(const vPoint& point)
	{
		this->addPointClick(std::make_shared<vPoint>(point));
	}

	void MockView::emulateRemovePointClick(const vPoint& point)
	{
		this->removePointClick(std::make_shared<vPoint>(point));
	}

}