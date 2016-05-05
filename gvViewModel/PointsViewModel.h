#pragma once 

#include "PointViewModel.h"
#include "../gvModel/IPlan.h"
#include "../gvModel/PlanManager.h"



namespace gv
{
	namespace View
	{
		public ref class PointsViewModel
		{
			BindingList<PointViewModel^>^ _pointsVM;

			Model::IPlan* _plan;
			Model::PlanManager& _planManager;

			int pointAddedSubscId;
			int pointRemovedSubscId;		
			delegate void collectionChanged(const std::shared_ptr<IPoint> point);
			collectionChanged^ _pointAddedDel;
			collectionChanged^ _pointRemovedDel;

		public:

			BindingList<PointViewModel^>^ GetPoints()
			{
				return _pointsVM;
			}


			PointsViewModel(Model::PlanManager& planManager) : _planManager(planManager), _plan(planManager.getPlan())
			{
				_pointsVM = gcnew BindingList<PointViewModel^>();

				auto planPoints = _plan->getPointsOnlyRead();
				for (const std::shared_ptr<IPoint> point : planPoints)
				{
					_pointsVM->Add(gcnew PointViewModel(point.get()));
				}

				//Warning! You must save delagates reference as class member
				_pointAddedDel =  gcnew collectionChanged(this, &PointsViewModel::modelPointAddedEvent);
				_pointRemovedDel =  gcnew collectionChanged(this, &PointsViewModel::modelPointRemovedEvent);
				pointAddedSubscId = 
					(CLIHelper::SubscribeDelegateToUnmanagedEvent(_pointAddedDel, _plan->pointAdded));
				pointRemovedSubscId = 
					(CLIHelper::SubscribeDelegateToUnmanagedEvent(_pointRemovedDel, _plan->pointRemoved));
			}

			~PointsViewModel()
			{
				_plan->pointAdded -= pointAddedSubscId;
				_plan->pointRemoved -= pointRemovedSubscId;
			}

			//invoking form model
		private:
			void modelPointAddedEvent(const std::shared_ptr<IPoint> newPoint)
			{
				_pointsVM->Add(gcnew PointViewModel(newPoint.get()));
			}

			void modelPointRemovedEvent(const std::shared_ptr<IPoint> removedPoint)
			{
				int pointVMIndex = -1;
				for (int i = 0; i < _pointsVM->Count; i++)
				{
					if (_pointsVM[i]->getModelPoint() == removedPoint.get())
					{
						pointVMIndex = i;
					}
				}
				_pointsVM->RemoveAt(pointVMIndex);
			}
		};
	}
}