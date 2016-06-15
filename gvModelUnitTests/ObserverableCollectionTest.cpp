#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <list>
#include <string>
#include <algorithm>
#include <memory>

#include <ObserverableCollection.h>

#include "Call.h"


namespace gvModelUnitTests
{		
	TEST_CLASS(ObserverableCollectionTest)
	{
		std::shared_ptr<CallWithValue<int> > _call;

		void ItemAdded(const skb::ItemAddedEventArgs<int>& arg)
		{
			_call = std::make_shared<CallWithValue<int> >(Method::itemAddedEventMethod, "", arg.item);
		}


		void ItemRemoved(const skb::ItemRemovedEventArgs<int>& arg)
		{
			_call = std::make_shared<CallWithValue<int> >(Method::itemRemovedEventMethod, "", arg.item);
		}
	public:

		TEST_METHOD(AddItemTest)
		{
			skb::ObserverableCollection< std::list, int > col;

			int subsriptionId = (col.pointAdded += std::bind(&ObserverableCollectionTest::ItemAdded, this, std::placeholders::_1));
			int testItem1 = 11;

			col.append(testItem1);
			const int& item1 =  col.getItems()->front();
			if (col.getItems()->size() != 1 || item1 != testItem1)
				Assert::Fail();

			CallWithValue<int> requierdCall(Method::itemAddedEventMethod, "", &item1);
			if (requierdCall != *_call)
				Assert::Fail();



			int testItem2 = 34;
			col.append(testItem2);
			const int& item2 =  col.getItems()->back();
			if (col.getItems()->size() != 2 || item2 != testItem2)
				Assert::Fail();

			CallWithValue<int> requierdCall2(Method::itemAddedEventMethod, "", &item2);
			if (requierdCall2 != *_call)
				Assert::Fail();

			col.pointAdded -= subsriptionId;
		}



		TEST_METHOD(RemoveItemTest)
		{
			skb::ObserverableCollection< std::list, int > col;
			int subsriptionId = (col.pointRemoved += std::bind(&ObserverableCollectionTest::ItemRemoved, this, std::placeholders::_1));

			int testItem1 = 11;
			int testItem2 = 34;

			col.append(testItem1);
			col.append(testItem2);

			const int& item1 = col.getItems()->front();

			col.remove(&item1);
			CallWithValue<int> requierdCall(Method::itemRemovedEventMethod, "", &item1);

			if (col.getItems()->size() != 1 || col.getItems()->front() != testItem2)
				Assert::Fail();


			if (requierdCall != *_call)
				Assert::Fail();
		}
	};
}