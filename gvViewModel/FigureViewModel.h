#pragma once 

#include "PlanElementViewModel.h"

namespace gv
{
	namespace Model
	{
		class Figure;
	}

	namespace ViewModel
	{
		public ref class FigureViewModel : public PlanElementViewModel
		{
		public:
			FigureViewModel(const Model::Figure* figure) : PlanElementViewModel(figure)
			{}
		};
	}
}