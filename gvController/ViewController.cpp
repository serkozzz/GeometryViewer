#include "ViewController.h"

using namespace gv;
using namespace gv::Controller;



ViewController::ViewController(View::IView* view, Model::Model* model) : _view(view), 
	_model(model), 
	_planManager(model->getPlanManager())
{

	//view events
	addPointClickSubscription = 
		(_view->addPointClick += std::bind(&ViewController::addPointClick, this, std::placeholders::_1));
	removePointClickSubscription = 
		(_view->removePointClick += std::bind(&ViewController::removePointClick, this, std::placeholders::_1));
	changePointSizeSubscription = 
		(_view->changePointSizeClick += std::bind(&ViewController::changePointSizeClick, this, std::placeholders::_1));
	loadPlanClickSubscription =
		(_view->loadPlanClick += std::bind(&ViewController::loadPlanClick, this, std::placeholders::_1));
	savePlanClickSubscription = 
		(_view->savePlanClick += std::bind(&ViewController::savePlanClick, this, std::placeholders::_1));


	//model events
	auto plan = _planManager.getPlan();
	pointAddedSubscription =
		(plan->pointAdded += std::bind(&ViewController::pointAdded, this, std::placeholders::_1));
	pointRemovedSubscription = 
		(plan->pointRemoved += std::bind(&ViewController::pointRemoved, this, std::placeholders::_1));

	plan->getCamera()->propertyChanged	+= std::bind(&ViewController::cameraPropertyChanged, this, 
		std::placeholders::_1);

}


ViewController::~ViewController()
{
	_view->addPointClick -= addPointClickSubscription;
	_view->removePointClick -= removePointClickSubscription;
	_view->changePointSizeClick -= changePointSizeSubscription;
	_view->loadPlanClick -= loadPlanClickSubscription;
	_view->savePlanClick -= savePlanClickSubscription;
}

#pragma region View Events
void ViewController::addPointClick(const std::shared_ptr<IPoint>& p)
{
	_planManager.tryAddPoint(p);
}


void ViewController::removePointClick(const std::shared_ptr<IPoint>& p)
{
	_planManager.tryRemovePoint(p);
}


void ViewController::changePointSizeClick(int newSize)
{

}

void ViewController::loadPlanClick(const std::string&)
{

}

void ViewController::savePlanClick(const std::string&)
{

}
#pragma endregion View Events

#pragma region Model Events
void ViewController::pointAdded(const std::shared_ptr<IPoint>& p)
{
	_view->pointAdded(p);
}


void ViewController::pointRemoved(const std::shared_ptr<IPoint>& p)
{
	_view->pointRemoved(p);
}

void ViewController::cameraPropertyChanged(gv::Model::CameraPropChangedArgs args)
{
	gv::Model::ICamera* camera = _planManager.getPlan()->getCamera();
	float matrix[16];
	for(int i = 0; i < 4; i++)
	{
		matrix[i*4] = camera->getTransform()[i][0];
		matrix[i*4 + 1] = camera->getTransform()[i][1];
		matrix[i*4 + 2] = camera->getTransform()[i][2];
		matrix[i*4 + 3] = camera->getTransform()[i][3];
	}
	_view->cameraMatrixChanged(matrix);
}

#pragma endregion Model Events