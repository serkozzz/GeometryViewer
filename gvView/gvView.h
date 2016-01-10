#pragma once

#include "IView.h"

namespace gv
{
	namespace View
	{

		class gvView : public IView
		{
		private:
			std::shared_ptr<IPoint> _selectedPoint;
			int pointPropChangedSubscriptionId;



			void selectedPointPropertyChanged(PointPropChangedArgs arg)
			{
				if (selectedPointPropChangedEvent != nullptr)
					selectedPointPropChangedEvent(arg);
			}


		public:

			std::shared_ptr<IPoint>& getSelectedPoint()
			{
				return _selectedPoint;
			}

			void pointAdded(const std::shared_ptr<IPoint>& p)
			{
				if(pointAddedEvent != nullptr)
					pointAddedEvent(p);
			}

			void pointRemoved(const std::shared_ptr<IPoint>& p)
			{
				if(pointRemovedEvent != nullptr)
					pointRemovedEvent(p);
			}

			void pointSelected(const std::shared_ptr<IPoint>& p)
			{
				/*if (_selectedPoint != nullptr)
				_selectedPoint->propertyChanged -= pointPropChangedSubscriptionId;*/

				_selectedPoint = p;
				pointPropChangedSubscriptionId = (_selectedPoint->propertyChanged += 
					std::bind(&gvView::selectedPointPropertyChanged, this, std::placeholders::_1)); 

				if(pointSelectedEvent != nullptr)
					pointSelectedEvent(p);
			}

			void pointUnSelected(const std::shared_ptr<IPoint>& p)
			{
				_selectedPoint->propertyChanged -= pointPropChangedSubscriptionId;
				_selectedPoint.reset();
				if(pointUnselectedEvent != nullptr)
					pointUnselectedEvent(p);
			}

			skb::EventHandler<std::shared_ptr<IPoint> > pointAddedEvent;
			skb::EventHandler<std::shared_ptr<IPoint> > pointRemovedEvent;
			skb::EventHandler<std::shared_ptr<IPoint> > pointSelectedEvent;
			skb::EventHandler<std::shared_ptr<IPoint> > pointUnselectedEvent;

			skb::EventHandler<PointPropChangedArgs> selectedPointPropChangedEvent;
		};
	}
}