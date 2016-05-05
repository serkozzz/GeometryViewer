#pragma once

#include "../gvModel/PlanManager.h"
#include "PointsViewModel.h"

namespace gv 
{
	namespace View
	{
		public ref class MainViewModel : INotifyPropertyChanged
		{
			PointViewModel^ _selectedPoint;
			Model::PlanManager& _planManager;

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

		public:
			virtual event PropertyChangedEventHandler^ PropertyChanged;


			property PointsViewModel^ PointsVM;

			MainViewModel(Model::PlanManager& planManager) : _planManager(planManager)
			{
				PointsVM = gcnew PointsViewModel(planManager);
				_selectedPoint = nullptr;
			}

		public:
			//invoking from View
			void viewCreatePointCommand()
			{
				_planManager.createNewPoint();
				auto pointsList = PointsVM->GetPoints();
				SelectedPoint = pointsList[pointsList->Count - 1];
			}

		};
	}
}