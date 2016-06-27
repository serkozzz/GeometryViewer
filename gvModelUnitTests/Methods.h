#pragma once

#include <list>

namespace gvModelUnitTests
{	
	enum Methods
	{
		planElementPropChangedMethods,
		pointPropChangedMethods,
		planElementTryPropChangedMethods,
		pointTryPropChangedMethods,
		itemAddedEventMethods,
		itemRemovedEventMethods,

		copyConstructor,
		moveConstructor,
		copyAssignmentOperator,
		moveAssignmentOperator
	};


	class callsDispatcher
	{
	protected:
		static std::list<Methods> _calls;
		static void addCall(Methods method)
		{
			_calls.push_back(method);
		}
	public:
		static void clearMethodCallList()
		{
			_calls.clear();
		}

		static const std::list<Methods>& getMethodCallList()
		{
			return _calls;
		}
	};


}


