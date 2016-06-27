#include "stdafx.h"

#include "CallsDispatcher.h"


namespace skb
{	
	namespace UnitTestUtils
	{
		std::list<std::shared_ptr<BaseCall> > CallsDispatcher::_calls;
	}
}