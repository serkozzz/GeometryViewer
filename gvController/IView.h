#pragma once

#include "../EventHandler/EventHandler.h"
#include "IPointData.h"

namespace gv
{
	class IView
	{
	public:
		skb::EventHandler<IPointData> addPointClick;
		skb::EventHandler<std> addPointClick;
	};
}
