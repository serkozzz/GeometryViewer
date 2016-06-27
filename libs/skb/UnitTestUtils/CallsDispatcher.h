#pragma once

#include <list>
#include <memory>

#include "BaseCall.h"


namespace skb
{	
	namespace UnitTestUtils
	{
		class CallsDispatcher
		{
		protected:
			static std::list<std::shared_ptr<BaseCall> > _calls;
			static void addCall(const std::shared_ptr<BaseCall>& method)
			{
				_calls.push_back(method);
			}
		public:
			static void clearMethodCallList()
			{
				_calls.clear();
			}

			static const std::list<std::shared_ptr<BaseCall>>& getMethodCallList()
			{
				return _calls;
			}
		};
	}
}