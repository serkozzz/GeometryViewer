#pragma once

#include "EventHandler.h"
#include "vPoint.h"
#include <memory>



namespace gv
{
	namespace gvView
	{

		///to work with property changed events use vPoint class 
		///It has appropriate EventHandlers propertyChanged and tryPropertyChange

		class IView
		{
		public:
			//to controller     <------ 
			//GUI events:
			//EventHandler<PropertyChangedArgs> 
			skb::EventHandler<const std::shared_ptr<vPoint>& > addPointClick;
			skb::EventHandler<const std::shared_ptr<vPoint>& > removePointClick;
			//here can be added selection by gui events
			skb::EventHandler<int> changePointSizeClick;
			skb::EventHandler<const std::string&> loadPlanClick;
			skb::EventHandler<const std::string&> savePlanClick;



			//from controller   ------> 
			virtual void pointAdded(const std::shared_ptr<vPoint>& p) = 0;
			virtual void pointRemoved(const std::shared_ptr<vPoint>& p) = 0;
			virtual void pointSelected(const std::shared_ptr<vPoint>& p) = 0;
			virtual void pointUnSelected(const std::shared_ptr<vPoint>& p) = 0;
		};
	}
}