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
			skb::EventHandler<const std::shared_ptr<IPoint>& > pointAdded;
			skb::EventHandler<const std::shared_ptr<IPoint>& > pointRemoved;
		};

	}
}