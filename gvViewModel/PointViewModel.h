#pragma once 

#include "PlanElementViewModel.h"

namespace gv
{
	namespace Model
	{
		class Point;
	}

	namespace ViewModel
	{
		public ref class PointViewModel : public PlanElementViewModel
		{
		public:
			PointViewModel(const Model::Point* point) : PlanElementViewModel(point)
			{}
		};
	}
}