#pragma once

#include "../EventHandler/EventHandler.h"
#include "vPointData.h"

namespace gv
{
	class IView
	{
	public:
		skb::EventHandler<vPointData> addPointClick;
		skb::EventHandler<std> addPointClick;
	};
}
