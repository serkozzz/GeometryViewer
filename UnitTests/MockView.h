#pragma once

#include "../gvView/IView.h"
#include "../gvView/vPoint.h"
#include "EventHandler.h"
#include <map>
#include <memory>

namespace UnitTests
{
	class MockView : public gv::View::IView
	{
	public:

		//std::map<std::shared_ptr<gv::IPoint>, std::shared_ptr<gv::View::vPoint> > _vPoints;

		virtual void pointAdded(const std::shared_ptr<gv::IPoint>& p);

		virtual void pointRemoved(const std::shared_ptr<gv::IPoint>& p);

		virtual void pointSelected(const std::shared_ptr<gv::IPoint>& p);

		virtual void pointUnSelected(const std::shared_ptr<gv::IPoint>& p);

		virtual void cameraMatrixChanged(float newMatrix[16]);

		void emulateAddPointClick(const gv::View::vPoint& point);
		void emulateRemovePointClick(const gv::View::vPoint& point);

		//void onTryPointPropChanged(gv::PointPropChangedArgs args);

	};
}