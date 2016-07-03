#include <msclr\marshal_cppstd.h>

#include <list>

#include "CLIHelper.h"
#include "PointsCollectionViewModel.h"


using namespace System::ComponentModel;
using namespace msclr::interop;
using namespace gv::ViewModel;
using namespace gv::Model;


PointsCollectionViewModel::PointsCollectionViewModel(PointsCollection* pointsCollection) : _pointsCollection(pointsCollection)
{
	_pointsVMList = gcnew BindingList<PointViewModel^>();

	pointsCollection->startEnumeration();
	while (const Point* point = pointsCollection->nextItem())
	{
		_pointsVMList->Add(gcnew PointViewModel(point));
	}

	//Warning! You must save delagates reference as class member
	_pointAddedDel =  gcnew pointAdded(this, &PointsCollectionViewModel::modelPointAddedEvent);
	_pointRemovedDel =  gcnew pointRemoved(this, &PointsCollectionViewModel::modelPointRemovedEvent);
	pointAddedSubscId = 
		(CLIHelper::SubscribeDelegateToUnmanagedEvent(_pointAddedDel, pointsCollection->itemAdded));
	pointRemovedSubscId = 
		(CLIHelper::SubscribeDelegateToUnmanagedEvent(_pointRemovedDel, pointsCollection->itemRemoved));
}


PointsCollectionViewModel::~PointsCollectionViewModel()
{
	_pointsCollection->itemAdded -= pointAddedSubscId;
	_pointsCollection->itemRemoved -= pointRemovedSubscId;
}

BindingList<PointViewModel^>^ PointsCollectionViewModel::GetPointsVMList()
{
	return _pointsVMList;
}


void PointsCollectionViewModel::modelPointAddedEvent(const skb::ItemAddedEventArgs<Point>& args)
{
	_pointsVMList->Add(gcnew PointViewModel(args.item));
}


void PointsCollectionViewModel::modelPointRemovedEvent(const skb::ItemRemovedEventArgs<Point>& args)
{
	int pointsVMListIndex = -1;
	for (int i = 0; i < _pointsVMList->Count; i++)
	{
		if (_pointsVMList[i]->getModelPlanElementPtr() == args.item)
		{
			pointsVMListIndex = i;
		}
	}

	if (pointsVMListIndex != -1)
		_pointsVMList->RemoveAt(pointsVMListIndex);
}


//invoking from View
void PointsCollectionViewModel::viewAddPointCommand()
{
	_pointsCollection->append(Point()


	_planManager.createNewPoint();
	auto pointsList = PointsVM->GetPoints();
	SelectedPoint = pointsList[pointsList->Count - 1];
}


void PointsCollectionViewModel::viewSelectPointCommand(int pointIndex)
{
	auto pointsList = PointsVM->GetPoints();
	if (pointIndex == pointsList->IndexOf(SelectedPoint))
		return;

	SelectedPoint = pointsList[pointIndex];

}


void PointsCollectionViewModel::viewRemovePointCommand(int pointIndex)
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