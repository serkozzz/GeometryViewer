#pragma once

#include <list>
#include <memory>

#include "IPlan.h"
#include "mPoint.h"

namespace gv
{
	namespace Model
	{
		class mPlan : public IPlan
		{
			std::list<std::shared_ptr<mPoint> > _points;
		public:
			void AddPoint(std::shared_ptr<mPoint> p);
			void RemovePoint(std::shared_ptr<mPoint> p);
		};
	}

}