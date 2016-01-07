#pragma once

#include "IView.h"

namespace gv
{
	namespace gvView
	{

		class gvView : public IView
		{
		private:
			std::shared_ptr<vPoint> _selectedPoint;
			int pointPropChangedSubscriptionId;



			void selectedPointPropertyChanged(std::string propName)
			{
				if (selectedPointPropChangedEvent != nullptr)
					selectedPointPropChangedEvent(propName);
			}


		public:

			std::shared_ptr<vPoint>& getSelectedPoint()
			{
				return _selectedPoint;
			}

			void pointAdded(const std::shared_ptr<vPoint>& p)
			{
				if(pointAddedEvent != nullptr)
					pointAddedEvent(p);
			}

			void pointRemoved(const std::shared_ptr<vPoint>& p)
			{
				if(pointRemovedEvent != nullptr)
					pointRemovedEvent(p);
			}

			void pointSelected(const std::shared_ptr<vPoint>& p)
			{
				/*if (_selectedPoint != nullptr)
				_selectedPoint->propertyChanged -= pointPropChangedSubscriptionId;*/

				_selectedPoint = p;
				pointPropChangedSubscriptionId = (_selectedPoint->propertyChanged += 
					std::bind(&gvView::selectedPointPropertyChanged, this, std::placeholders::_1)); 

				if(pointSelectedEvent != nullptr)
					pointSelectedEvent(p);
			}

			void pointUnSelected(const std::shared_ptr<vPoint>& p)
			{
				_selectedPoint->propertyChanged -= pointPropChangedSubscriptionId;
				_selectedPoint.reset();
				if(pointUnselectedEvent != nullptr)
					pointUnselectedEvent(p);
			}

			skb::EventHandler<std::shared_ptr<vPoint> > pointAddedEvent;
			skb::EventHandler<std::shared_ptr<vPoint> > pointRemovedEvent;
			skb::EventHandler<std::shared_ptr<vPoint> > pointSelectedEvent;
			skb::EventHandler<std::shared_ptr<vPoint> > pointUnselectedEvent;

			skb::EventHandler<const std::string&> selectedPointPropChangedEvent;

			void (CALLBACK *testMethod)(int);

			void TestCallback(std::shared_ptr<vPoint> p)
			{
				pointAdded(p);
			}
		};
	}
}