
#include <msclr\marshal_cppstd.h>

#include "CLIHelper.h"
#include "SelectedElementViewModel.h"





using namespace System::ComponentModel;
using namespace msclr::interop;
using namespace gv::ViewModel;
using namespace gv::Model;


SelectedElementViewModel::SelectedElementViewModel(PlanElement* planElement) : _planElement(planElement)
{			
	_propChangedDel =  gcnew propChanged(this, &SelectedElementViewModel::planElementPropertyChangedEvent);
	subscriptionId = 
		(CLIHelper::SubscribeDelegateToUnmanagedEvent(_propChangedDel, _planElement->propertyChanged));
}



SelectedElementViewModel::~SelectedElementViewModel()
{
	_planElement->propertyChanged -= subscriptionId;
}


void SelectedElementViewModel::planElementPropertyChangedEvent(PlanElementPropChangedArgs arg)
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


float SelectedElementViewModel::PositionX::get()
{
	return _planElement->getPosition().x;
}

void  SelectedElementViewModel::PositionX::set(float newx) 
{
	glm::vec3 pos = _planElement->getPosition();
	pos.x = newx;	
	_planElement->setPosition(pos);
}



float SelectedElementViewModel::PositionY::get() 
{
	return _planElement->getPosition().y;
}

void SelectedElementViewModel::PositionY::set(float newy) 
{
	glm::vec3 pos = _planElement->getPosition();
	pos.y = newy;	
	_planElement->setPosition(pos);
} 



float SelectedElementViewModel::PositionZ::get()
{
	return _planElement->getPosition().z;
}

void SelectedElementViewModel::PositionZ::set(float newz) 
{
	glm::vec3 pos = _planElement->getPosition();
	pos.z = newz;	
	_planElement->setPosition(pos);
}



float SelectedElementViewModel::RotationX::get()
{
	return _planElement->getRotationEuler().x;
}

void SelectedElementViewModel::RotationX::set(float newX)
{
	glm::vec3 rot = _planElement->getRotationEuler();
	rot.x = newX;	
	_planElement->setRotationEuler(rot);
}



float SelectedElementViewModel::RotationY::get()
{
	return _planElement->getRotationEuler().y;
}

void SelectedElementViewModel::RotationY::set(float newY)
{
	glm::vec3 rot = _planElement->getRotationEuler();
	rot.y = newY;	
	_planElement->setRotationEuler(rot);
}



float SelectedElementViewModel::RotationZ::get()
{
	return _planElement->getRotationEuler().z;
}

void SelectedElementViewModel::RotationZ::set(float newZ)
{
	glm::vec3 rot = _planElement->getRotationEuler();
	rot.z = newZ;	
	_planElement->setRotationEuler(rot);
}



float SelectedElementViewModel::ScaleX::get()
{
	return _planElement->getScale().x;
}

void SelectedElementViewModel::ScaleX::set(float newX)
{
	glm::vec3 scale = _planElement->getScale();
	scale.x = newX;	
	_planElement->setScale(scale);
}


float SelectedElementViewModel::ScaleY::get()
{
	return _planElement->getScale().y;
}

void SelectedElementViewModel::ScaleY::set(float newY)
{
	glm::vec3 scale = _planElement->getScale();
	scale.y = newY;	
	_planElement->setScale(scale);
}


float SelectedElementViewModel::ScaleZ::get()
{
	return _planElement->getScale().z;
}

void SelectedElementViewModel::ScaleZ::set(float newZ)
{
	glm::vec3 scale = _planElement->getScale();
	scale.z = newZ;	
	_planElement->setScale(scale);
}

#pragma endregion Transform



System::String^ SelectedElementViewModel::Name::get() 
{
	System::String^ name = gcnew System::String(_planElement->getName().c_str());
	return name;
}

void SelectedElementViewModel::Name::set(System::String^ newName) 
{
	std::string name = marshal_as<std::string>(newName);
	_planElement->setName(name);
}

