#pragma once

#include "../gvModel/IPlan.h"
#include "PointsViewModel.h"

namespace gv 
{
	namespace View
	{
		public ref class MainViewModel
		{
		public:
			PointsViewModel^ pointsVM;
			PointViewModel^ selectedPoint;

			MainViewModel(Model::IPlan* plan)
			{
				pointsVM = gcnew PointsViewModel(plan);
				selectedPoint = nullptr;
			}
		};
	}
}