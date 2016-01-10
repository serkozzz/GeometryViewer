#pragma once

#include <memory>
#include <map>

#include "mPlan.h"



namespace gv
{
	namespace Model
	{
		class PlanManager
		{
			mPlan _plan;

			std::map<std::shared_ptr<IPoint>, int> _subscriptions;

			void onTryPointPropChanged(PointPropChangedArgs args);
		public:
			~PlanManager();

			IPlan* getPlan();

			void tryAddPoint(const std::shared_ptr<IPoint>& point);
			void tryRemovePoint(const std::shared_ptr<IPoint>& point);
		
#ifdef UNIT_TESTS
			mPlan& getPlanRegerenceForTest()
			{
				return _plan;
			}
#endif
		};
	}
}

