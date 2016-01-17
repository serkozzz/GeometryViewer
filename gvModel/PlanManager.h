#pragma once

#include <memory>
#include <map>


#include "IPlan.h"


namespace gv
{
	namespace Model
	{
		class mPlan;

		class PlanManager
		{
			mPlan* _plan;

			std::map<std::shared_ptr<IPoint>, int> _subscriptions;

			void onTryPointPropChanged(PointPropChangedArgs args);
		public:
			PlanManager();
			~PlanManager();

			IPlan* getPlan();

			void tryAddPoint(const std::shared_ptr<IPoint>& point);
			void tryRemovePoint(const std::shared_ptr<IPoint>& point);

#ifdef UNIT_TESTS
			mPlan* getPlanRegerenceForTest()
			{
				return _plan;
			}
#endif
		};
	}
}

