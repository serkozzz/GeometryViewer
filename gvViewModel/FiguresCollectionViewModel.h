#pragma once

#include "../gvModel/Plan.h"
#include "FigureViewModel.h"

namespace gv
{
	namespace ViewModel
	{

		public ref class FiguresCollectionViewModel
		{
			int figureAddedSubscId;
			int figureRemovedSubscId;		

			delegate void figureAdded(const skb::ItemAddedEventArgs<Model::Figure>& args);
			delegate void figureRemoved(const skb::ItemRemovedEventArgs<Model::Figure>& args);
			figureAdded^ _figureAddedDel;
			figureRemoved^ _figureRemovedDel;


			System::ComponentModel::BindingList<FigureViewModel^>^ _figuresVMList;
			Model::FiguresCollection* _figuresCollection;
		public:

			FiguresCollectionViewModel(Model::FiguresCollection* figuresCollection);

			~FiguresCollectionViewModel();

			System::ComponentModel::BindingList<FigureViewModel^>^ GetFiguresVMList();
			//invoking form model
		private:
			void modelFigureAddedEvent(const skb::ItemAddedEventArgs<Model::Figure>& args);
			void modelFigureRemovedEvent(const skb::ItemRemovedEventArgs<Model::Figure>& args);
		};
	}
}