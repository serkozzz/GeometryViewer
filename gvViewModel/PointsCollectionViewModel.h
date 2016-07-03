#pragma once

#include "../gvModel/Plan.h"
#include "PointViewModel.h"

namespace gv
{
	namespace ViewModel
	{

		public ref class PointsCollectionViewModel
		{
			int pointAddedSubscId;
			int pointRemovedSubscId;		

			System::ComponentModel::BindingList<PointViewModel^>^ _pointsVMList;
			Model::PointsCollection* _pointsCollection;

			delegate void pointAdded(const skb::ItemAddedEventArgs<Model::Point>& args);
			delegate void pointRemoved(const skb::ItemRemovedEventArgs<Model::Point>& args);
			pointAdded^ _pointAddedDel;
			pointRemoved^ _pointRemovedDel;

			//invoking form model
			void modelPointAddedEvent(const skb::ItemAddedEventArgs<Model::Point>& args);
			void modelPointRemovedEvent(const skb::ItemRemovedEventArgs<Model::Point>& args);

		public:

			PointsCollectionViewModel(Model::PointsCollection* pointsCollection);

			~PointsCollectionViewModel();

			System::ComponentModel::BindingList<PointViewModel^>^ GetPointsVMList();

			//invoking from View
			void viewAddPointCommand();	
			void viewSelectPointCommand(int pointIndex);
			void viewRemovePointCommand(int pointIndex);
		};
	}
}