#pragma once 

#include "PointViewModel.h"
#include "../gvModel/IPlan.h"



namespace gv
{
	namespace View
	{
		public ref class PointsViewModel
		{
			BindingList<PointViewModel^>^ _pointsVM;
			Model::IPlan* _plan;

			int pointAddedSubscId;
			int pointRemovedSubscId;		
			delegate void collectionChanged(const std::shared_ptr<IPoint> point);
			collectionChanged^ pointAddedDel;
			collectionChanged^ pointRemovedDel;

		public:
			PointsViewModel(Model::IPlan* plan) : _plan(plan)
			{
				_pointsVM = gcnew BindingList<PointViewModel^>();

				auto planPoints = _plan->getPointsOnlyRead();
				for (const std::shared_ptr<IPoint> point : planPoints)
				{
					_pointsVM->Add(gcnew PointViewModel(point.get()));
				}

				//Warning! You must save delagates reference as class member
				pointAddedDel =  gcnew collectionChanged(this, &PointsViewModel::modelPointAddedEvent);
				pointRemovedDel =  gcnew collectionChanged(this, &PointsViewModel::modelPointRemovedEvent);
				pointAddedSubscId = 
					(CLIHelper::SubscribeDelegateToUnmanagedEvent(pointAddedDel, plan->pointAdded));
				pointRemovedSubscId = 
					(CLIHelper::SubscribeDelegateToUnmanagedEvent(pointRemovedDel, plan->pointRemoved));
			}

			~PointsViewModel()
			{
				_plan->pointAdded -= pointAddedSubscId;
				_plan->pointRemoved -= pointRemovedSubscId;
			}

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