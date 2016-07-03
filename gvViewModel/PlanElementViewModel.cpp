
#include <msclr\marshal_cppstd.h>

#include "CLIHelper.h"
#include "PlanElementViewModel.h"





using namespace System::ComponentModel;
using namespace msclr::interop;
using namespace gv::ViewModel;
using namespace gv::Model;


PlanElementViewModel::PlanElementViewModel(const PlanElement* planElement) : _planElement(planElement)
{			
	_propChangedDel =  gcnew propChanged(this, &PlanElementViewModel::planElementPropertyChangedEvent);
	subscriptionId = 
		(CLIHelper::SubscribeDelegateToUnmanagedEvent(_propChangedDel, _planElement->propertyChanged));
	subs
}



PlanElementViewModel::~PlanElementViewModel()
{
	_planElement->propertyChanged -= subscriptionId;
}

const PlanElement* PlanElementViewModel::getModelPlanElementPtr()
{
	return _planElement;
}


void PlanElementViewModel::planElementPropertyChangedEvent(PlanElementPropChangedArgs arg)
{
	if (arg.propName ==	PlanElement::namePropertyName)
	{
		PropertyChanged(this, gcnew PropertyChangedEventArgs("Name"));
	}
	else if (arg.propName == PlanElement::positionPropertyName)
	{
		PropertyChanged(this, gcnew PropertyChangedEventArgs("PositionX"));
		PropertyChanged(this, gcnew PropertyChangedEventArgs("PositionY"));
		PropertyChanged(this, gcnew PropertyChangedEventArgs("PositionZ"));
	}
	else if (arg.propName == PlanElement::rotationPropertyName)
	{
		PropertyChanged(this, gcnew PropertyChangedEventArgs("RotationX"));
		PropertyChanged(this, gcnew PropertyChangedEventArgs("RotationY"));
		PropertyChanged(this, gcnew PropertyChangedEventArgs("RotationZ"));
	}
	else if (arg.propName == PlanElement::scalePropertyName)
	{
		PropertyChanged(this, gcnew PropertyChangedEventArgs("ScaleX"));
		PropertyChanged(this, gcnew PropertyChangedEventArgs("ScaleY"));
		PropertyChanged(this, gcnew PropertyChangedEventArgs("ScaleZ"));
	}
}




#pragma region Transform


float PlanElementViewModel::PositionX::get()
{
	return _planElement->getPosition().x;
}

void  PlanElementViewModel::PositionX::set(float newx) 
{
	glm::vec3 pos = _planElement->getPosition();
	pos.x = newx;	
	_planElement->trySetPosition(pos);
}



float PlanElementViewModel::PositionY::get() 
{
	return _planElement->getPosition().y;
}

void PlanElementViewModel::PositionY::set(float newy) 
{
	glm::vec3 pos = _planElement->getPosition();
	pos.y = newy;	
	_planElement->trySetPosition(pos);
} 



float PlanElementViewModel::PositionZ::get()
{
	return _planElement->getPosition().z;
}

void PlanElementViewModel::PositionZ::set(float newz) 
{
	glm::vec3 pos = _planElement->getPosition();
	pos.z = newz;	
	_planElement->trySetPosition(pos);
}



float PlanElementViewModel::RotationX::get()
{
	return _planElement->getRotationEuler().x;
}

void PlanElementViewModel::RotationX::set(float newX)
{
	glm::vec3 rot = _planElement->getRotationEuler();
	rot.x = newX;	
	_planElement->trySetRotationEuler(rot);
}



float PlanElementViewModel::RotationY::get()
{
	return _planElement->getRotationEuler().y;
}

void PlanElementViewModel::RotationY::set(float newY)
{
	glm::vec3 rot = _planElement->getRotationEuler();
	rot.y = newY;	
	_planElement->trySetRotationEuler(rot);
}



float PlanElementViewModel::RotationZ::get()
{
	return _planElement->getRotationEuler().z;
}

void PlanElementViewModel::RotationZ::set(float newZ)
{
	glm::vec3 rot = _planElement->getRotationEuler();
	rot.z = newZ;	
	_planElement->trySetRotationEuler(rot);
}



float PlanElementViewModel::ScaleX::get()
{
	return _planElement->getScale().x;
}

void PlanElementViewModel::ScaleX::set(float newX)
{
	glm::vec3 scale = _planElement->getScale();
	scale.x = newX;	
	_planElement->trySetScale(scale);
}


float PlanElementViewModel::ScaleY::get()
{
	return _planElement->getScale().y;
}

void PlanElementViewModel::ScaleY::set(float newY)
{
	glm::vec3 scale = _planElement->getScale();
	scale.y = newY;	
	_planElement->trySetScale(scale);
}


float PlanElementViewModel::ScaleZ::get()
{
	return _planElement->getScale().z;
}

void PlanElementViewModel::ScaleZ::set(float newZ)
{
	glm::vec3 scale = _planElement->getScale();
	scale.z = newZ;	
	_planElement->trySetScale(scale);
}

#pragma endregion Transform



System::String^ PlanElementViewModel::Name::get() 
{
	System::String^ name = gcnew System::String(_planElement->getName().c_str());
	return name;
}

void PlanElementViewModel::Name::set(System::String^ newName) 
{
	std::string name = marshal_as<std::string>(newName);
	_planElement->trySetName(name);
}

