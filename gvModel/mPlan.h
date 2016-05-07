#pragma once

#include <list>
#include <memory>

#include "IPlan.h"
#include "mPoint.h"
#include "mCamera.h"

namespace gv
{
	namespace Model
	{
		class mPlan : public IPlan
		{
			std::list<std::shared_ptr<mPoint> > _points;
			mCamera _camera;

		public:
			virtual ICamera* getCamera();
			mCamera* getmCamera();

			void AddPoint(const std::shared_ptr<mPoint>& p);
			void RemovePoint(const std::shared_ptr<mPoint>& p);
			const std::list<std::shared_ptr<mPoint> >& getPoints() const;
			const std::list<std::shared_ptr<IPoint> > getPointsOnlyRead() const;
			bool isPointExist(const std::shared_ptr<const IPoint>& p) const; 
			std::shared_ptr<mPoint> getPointByPointer(const IPoint* p) const; 

		};
	}

}