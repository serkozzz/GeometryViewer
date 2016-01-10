#pragma once

#include "mPlan.h"
#include <memory>


namespace gv
{
	namespace Model
	{
		class PlanManager
		{
			mPlan _plan;
		public:
			IPlan* getPlan();
			void tryAddPoint(const std::shared_ptr<IPoint>& point);
			void tryRemovePoint(const std::shared_ptr<IPoint>& point);
		};
	}
}

