#pragma once

#include "PlanManager.h"


namespace gv
{
	namespace Model
	{
		class Model
		{
			PlanManager _planManager;
		public:
			PlanManager& getPlanManager()
			{
				return _planManager;
			}
		};
	}
}