#pragma once

#include <memory>
#include <map>


#include "Plan.h"
#include "CameraMover.h"

namespace gv
{
	namespace Model
	{
		class PlanManager
		{
			Plan _plan;
			std::shared_ptr<CameraMover> _cameraMover;

			std::map<const Point*, int> _subscriptions;

			void onFigureAdded(const FigureAddedEventArgs& arg);
			void onFigureRemoved(const FigureRemovedEventArgs& arg);

			void onTryPointPropChanged(PointPropChangedArgs args);


		public:
			PlanManager();

			const Plan* getPlan() const;

//#ifdef UNIT_TESTS
//			mPlan* getPlanRegerenceForTest()
//			{
//				return _plan;
//			}
//#endif
		};
	}
}

