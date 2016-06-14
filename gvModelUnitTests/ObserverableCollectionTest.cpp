#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <list>
#include <string>
#include <algorithm>
#include <ObserverableCollection.h>

#include "Call.h"


namespace gvModelUnitTests
{		
	TEST_CLASS(ObserverableCollectionTest)
	{

		TEST_METHOD(ObserverableCollectionTest1)
		{
			skb::ObserverableCollection< std::list, int > col;
			int a = 11;
			col.append(&a);


			Call call11(Method::itemAddedEventMethod, "");
			Call call12(Method::itemRemovedEventMethod, "11");
			call12 = call11;

			CallWithValue<int> call(Method::itemAddedEventMethod, "", &a);
			CallWithValue<int> call2(Method::itemRemovedEventMethod, "2222", &a);
			call2 = call;

		}
	};
}