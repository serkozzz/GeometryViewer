#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <list>
#include <string>
#include <algorithm>
#include <ObserverableCollection.h>




namespace gvModelUnitTests
{		
	TEST_CLASS(ObserverableCollectionTest)
	{

		TEST_METHOD(ObserverableCollectionTest1)
		{
			skb::ObserverableCollection< std::list, int > col;
			col._collection.push_back(90);

		}
	};
}