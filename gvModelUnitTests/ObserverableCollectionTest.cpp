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
			_call = std::make_shared<CallWithValue<int> >(Methods::itemAddedEventMethods, "", arg.item);
		}


		void ItemRemoved(const skb::ItemRemovedEventArgs<int>& arg)
		{
			_call = std::make_shared<CallWithValue<int> >(Methods::itemRemovedEventMethods, "", arg.item);
		}


		class rValueTestClass : public callsDispatcher
		{
			char* buffer;
		public:
			rValueTestClass(const char* str) : buffer(new char[strlen(str) + 1])
			{
				strcpy(buffer, str);
			}

			~rValueTestClass()
			{
				delete buffer;
			}

			rValueTestClass(const rValueTestClass& other) : buffer(new char[strlen(other.buffer) + 1])
			{
				strcpy(buffer, other.buffer);
				rValueTestClass::addCall(Methods::copyConstructor);
			}


			//TODO swap
			rValueTestClass(rValueTestClass&& other)
			{
				buffer = other.buffer;
				other.buffer = nullptr;
				rValueTestClass::addCall(Methods::moveConstructor);
			}


			void operator=(rValueTestClass other)
			{
				std::swap(buffer, other.buffer);
			}

		};
	public:

		TEST_METHOD(AppendTest)
		{
			skb::ObserverableCollection< std::list, int > col;

			int subsriptionId = (col.pointAdded += std::bind(&ObserverableCollectionTest::ItemAdded, this, std::placeholders::_1));
			int testItem1 = 11;

			col.append(testItem1);
			const int* item1 =  &col.getItems()->front();
			if (col.getItems()->size() != 1 || *item1 != testItem1)
				Assert::Fail();

			CallWithValue<int> requierdCall(Methods::itemAddedEventMethods, "", item1);
			if (requierdCall != *_call)
				Assert::Fail();



			int testItem2 = 34;
			col.append(testItem2);
			const int* item2 =  &col.getItems()->back();
			if (col.getItems()->size() != 2 || *item2 != testItem2)
				Assert::Fail();

			CallWithValue<int> requierdCall2(Methods::itemAddedEventMethods, "", item2);
			if (requierdCall2 != *_call)
				Assert::Fail();

			col.pointAdded -= subsriptionId;
		}


		TEST_METHOD(InsertTest)
		{
			skb::ObserverableCollection< std::list, int > col;

			int subsriptionId = (col.pointAdded += std::bind(&ObserverableCollectionTest::ItemAdded, this, std::placeholders::_1));
			int testItem1 = 11;
			int testItem2 = 34;
			int insertableItem = 88;


			col.append(testItem1);
			col.append(testItem2);

			col.insert(insertableItem, &col.getItems()->back());

			auto it = col.getItems()->begin();
			it++;

			const int* item2 = &(*it);
			if (col.getItems()->size() != 3 || *item2 != insertableItem)
				Assert::Fail();

			CallWithValue<int> requierdCall(Methods::itemAddedEventMethods, "", item2);
			if (requierdCall != *_call)
				Assert::Fail();



			int insertableItem2 = 112;
			col.insert(insertableItem2, nullptr);

			const int& item4 = col.getItems()->back();
			if (col.getItems()->size() != 4 || item4 != insertableItem2)
				Assert::Fail();

			CallWithValue<int> requierdCall2(Methods::itemAddedEventMethods, "", &item4);
			if (requierdCall2 != *_call)
				Assert::Fail();

			col.pointAdded -= subsriptionId;
		}


		TEST_METHOD(RemoveTest)
		{
			skb::ObserverableCollection< std::list, int > col;
			int subsriptionId = (col.pointRemoved += std::bind(&ObserverableCollectionTest::ItemRemoved, this, std::placeholders::_1));

			int testItem1 = 11;
			int testItem2 = 34;

			col.append(testItem1);
			col.append(testItem2);

			const int* item1 = &col.getItems()->front();

			col.remove(item1);
			CallWithValue<int> requierdCall(Methods::itemRemovedEventMethods, "", item1);

			if (col.getItems()->size() != 1 || col.getItems()->front() != testItem2)
				Assert::Fail();


			if (requierdCall != *_call)
				Assert::Fail();
		}


		TEST_METHOD(MoveSemanticsTest)
		{
			skb::ObserverableCollection< std::list, rValueTestClass > col;
			rValueTestClass testItem1("Obj 1");
			col.append(std::move(testItem1));

			auto callsList = rValueTestClass::getMethodCallList();
			if (std::find(callsList.begin(), callsList.end(), Methods::moveConstructor) == callsList.end())
				Assert::Fail();

			if (col.getItems()->size() != 1)
				Assert::Fail();

			col.append(rValueTestClass("Obj 2"));

			auto it = col.getItems()->begin();
			it++;
			const rValueTestClass* item2Ptr = &(*it);

			rValueTestClass::clearMethodCallList();
			col.insert(rValueTestClass("insertableObj"), item2Ptr);

			if (std::find(callsList.begin(), callsList.end(), Methods::moveConstructor) == callsList.end())
				Assert::Fail();

			if (col.getItems()->size() != 3)
				Assert::Fail();

		}
	};
}