#include <msclr\marshal_cppstd.h>

#include <list>

#include "CLIHelper.h"
#include "FiguresCollectionViewModel.h"


using namespace System::ComponentModel;
using namespace msclr::interop;
using namespace gv::ViewModel;
using namespace gv::Model;


FiguresCollectionViewModel::FiguresCollectionViewModel(FiguresCollection* figuresCollection) : _figuresCollection(figuresCollection)
{
	_figuresVMList = gcnew BindingList<FigureViewModel^>();

	figuresCollection->startEnumeration();
	while (const Figure* figure = figuresCollection->nextItem())
	{
		_figuresVMList->Add(gcnew FigureViewModel(figure));
	}

	//Warning! You must save delagates reference as class member
	_figureAddedDel =  gcnew figureAdded(this, &FiguresCollectionViewModel::modelFigureAddedEvent);
	_figureRemovedDel =  gcnew figureRemoved(this, &FiguresCollectionViewModel::modelFigureRemovedEvent);
	figureAddedSubscId = 
		(CLIHelper::SubscribeDelegateToUnmanagedEvent(_figureAddedDel, figuresCollection->itemAdded));
	figureRemovedSubscId = 
		(CLIHelper::SubscribeDelegateToUnmanagedEvent(_figureRemovedDel, figuresCollection->itemRemoved));
}


FiguresCollectionViewModel::~FiguresCollectionViewModel()
{
	_figuresCollection->itemAdded -= figureAddedSubscId;
	_figuresCollection->itemRemoved -= figureRemovedSubscId;
}

BindingList<FigureViewModel^>^ FiguresCollectionViewModel::GetFiguresVMList()
{
	return _figuresVMList;
}


void FiguresCollectionViewModel::modelFigureAddedEvent(const skb::ItemAddedEventArgs<Figure>& args)
{
	_figuresVMList->Add(gcnew FigureViewModel(args.item));
}


void FiguresCollectionViewModel::modelFigureRemovedEvent(const skb::ItemRemovedEventArgs<Figure>& args)
{
	int figuresVMListIndex = -1;
	for (int i = 0; i < _figuresVMList->Count; i++)
	{
		if (_figuresVMList[i]->getModelPlanElementPtr() == args.item)
		{
			figuresVMListIndex = i;
		}
	}

	if (figuresVMListIndex != -1)
		_figuresVMList->RemoveAt(figuresVMListIndex);
}