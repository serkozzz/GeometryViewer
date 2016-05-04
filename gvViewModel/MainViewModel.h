#pragma once

#include "../gvModel/IPlan.h"
#include "PointsViewModel.h"

namespace gv 
{
	namespace View
	{
		public ref class MainViewModel : INotifyPropertyChanged
		{
			PointViewModel^ _selectedPoint;

		public:
			property PointViewModel^ SelectedPoint
			{
				PointViewModel^ get() 
				{
					return _selectedPoint;
				}

				void set(PointViewModel^ newSelectedPoint) 
				{
					SelectedPoint = newSelectedPoint;
					PropertyChanged(this, gcnew PropertyChangedEventArgs("SelectedPoint"));
				}
			}

			property PointsViewModel^ pointsVM;

			MainViewModel(Model::IPlan* plan)
			{
				pointsVM = gcnew PointsViewModel(plan);
				_selectedPoint = nullptr;
			}

		public:
			virtual event PropertyChangedEventHandler^ PropertyChanged;
		};
	}
}