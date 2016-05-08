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
					_selectedPoint = newSelectedPoint;
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


			void viewSelectPointCommand(int pointIndex)
			{
				auto pointsList = PointsVM->GetPoints();
				if (pointIndex == pointsList->IndexOf(SelectedPoint))
					return;

				SelectedPoint = pointsList[pointIndex];

			}


			void viewRemovePointCommand(int pointIndex)
			{
				auto pointsList = PointsVM->GetPoints();
				if (pointIndex >= pointsList->Count)
					throw std::logic_error("ViewModel: attemption of removing point with unexisted index");

				PointViewModel^ removingPoint = pointsList[pointIndex];


				if (removingPoint == SelectedPoint)
				{
					if (pointIndex + 1 < pointsList->Count)
						SelectedPoint = pointsList[pointIndex + 1];
					else if (pointIndex > 0)
						SelectedPoint = pointsList[pointIndex - 1];
					else 
						SelectedPoint = nullptr;
				}
				_planManager.removePoint(removingPoint->getModelPoint());

			}
		};
	}
}