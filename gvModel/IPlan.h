#pragma once

#include <memory>
#include <list>


#include "EventHandler.h"
#include "IPoint.h"
#include "ICamera.h"



namespace gv
{
	namespace Model
	{

		class IPlan
		{
		public:
			virtual ICamera* getCamera() = 0;
			virtual const std::list<std::shared_ptr<IPoint> > getPointsOnlyRead() const = 0;

			skb::EventHandler<const std::shared_ptr<IPoint>& > pointAdded;
			skb::EventHandler<const std::shared_ptr<IPoint>& > pointRemoved;
		};

	}
}