#pragma once

#include "EventHandler.h"
#include "IPoint.h"
#include <memory>


namespace gv
{
	namespace Model
	{

		class IPlan
		{
		public:
			skb::EventHandler<std::shared_ptr<IPoint> > pointAdded;
			skb::EventHandler<std::shared_ptr<IPoint> > pointRemoved;
		};

	}
}