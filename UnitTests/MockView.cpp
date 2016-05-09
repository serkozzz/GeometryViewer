#include "stdafx.h"

#include "MockView.h"

using namespace gv;
using namespace gv::View;

namespace UnitTests
{
	void MockView::pointAdded(const std::shared_ptr<IPoint>& p)
	{
		//_vPoints[p] = std::make_shared<vPoint>(vPoint(p.get()));
	}


	void MockView::pointRemoved(const std::shared_ptr<gv::IPoint>& p)
	{
		//auto it = _vPoints.find(p);
		//if (it == _vPoints.end())
		//{
		//	throw std::exception("MockView: Attemption to delete point that is abscent in the view");
		//}
		//_vPoints.erase(it->first);
	}


	void MockView::pointSelected(const std::shared_ptr<gv::IPoint>& p)
	{

	}


	void MockView::pointUnSelected(const std::shared_ptr<gv::IPoint>& p)
	{

	}

	void MockView::cameraMatrixChanged(float newMatrix[16])
	{

	}

	void MockView::emulateAddPointClick(const vPoint& point)
	{
		//this->addPointClick(std::make_shared<vPoint>(point));
	}

	void MockView::emulateRemovePointClick(const vPoint& point)
	{
		//this->removePointClick(std::make_shared<vPoint>(point));
	}

}