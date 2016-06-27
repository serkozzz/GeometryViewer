#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <list>
#include <string>
#include <algorithm>
#include <memory>

#include <EventHandler/ObserverableCollection.h>

#include <UnitTestUtils/BaseCall.h>
#include <UnitTestUtils\TestClass.h>

using namespace skb::UnitTestUtils;



namespace gvModelUnitTests
{		
	TEST_CLASS(ObserverableCollectionTest)
	{
		template<typename T>
		struct Call : public BaseCall
		{
			Call(int methodType, std::string propertyName, const T* value) 
				: BaseCall(methodType), methodType(methodType), propertyName(propertyName), value(value)
			{
			}

			enum
			{
				Method_itemAddedEvent,
				Method_itemRemovedEvent,
			};


			bool operator== (const Call& other)
			{
				if (this->methodType != other.methodType)
					return false;
				if (this->propertyName != other.propertyName)
					return false;
				if (this->value != other.value)
					return false;

				return true;
			}

		private:
			int methodType;
			std::string propertyName;
			const T* value;

		};


		std::shared_ptr<Call<int> > _call;

		void ItemAdded(const skb::ItemAddedEventArgs<int>& arg)
		{
			_call = std::make_shared<Call<int> >(Call<int>::Method_itemAddedEvent, "", arg.item);
		}


		void ItemRemoved(const skb::ItemRemovedEventArgs<int>& arg)
		{
			_call = std::make_shared<Call<int> >(Call<int>::Method_itemRemovedEvent, "", arg.item);
		}

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

			Call<int> requierdCall(Call<int>::Method_itemAddedEvent, "", item1);
			if (requierdCall != *_call)
				Assert::Fail();



			int testItem2 = 34;
			col.append(testItem2);
			const int* item2 =  &col.getItems()->back();
			if (col.getItems()->size() != 2 || *item2 != testItem2)
				Assert::Fail();

			Call<int> requierdCall2(Call<int>::Method_itemAddedEvent, "", item2);
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

			Call<int> requierdCall(Call<int>::Method_itemAddedEvent, "", item2);
			if (requierdCall != *_call)
				Assert::Fail();



			int insertableItem2 = 112;
			col.insert(insertableItem2, nullptr);

			const int* item4 = &col.getItems()->back();
			if (col.getItems()->size() != 4 || *item4 != insertableItem2)
				Assert::Fail();

			Call<int> requierdCall2(Call<int>::Method_itemAddedEvent, "", item4);
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
			Call<int> requierdCall(Call<int>::Method_itemRemovedEvent, "", item1);

			if (col.getItems()->size() != 1 || col.getItems()->front() != testItem2)
				Assert::Fail();


			if (requierdCall != *_call)
				Assert::Fail();
		}


		TEST_METHOD(MoveSemanticsTest)
		{
			skb::ObserverableCollection< std::list, SimpleTestClass > col;
			SimpleTestClass testItem1("Obj 1");
			col.append(std::move(testItem1));

			auto callsList = SimpleTestClass::getMethodCallList();
			const BaseCall moveConstructorCall(BaseCall::Method_Move_Constructor);

			if (std::find_if(callsList.begin(), callsList.end(), [&moveConstructorCall] (const std::shared_ptr<BaseCall>& call) -> bool
			{
				return (*call) == moveConstructorCall;
			}) == callsList.end())
			{
				Assert::Fail();
			}



			if (col.getItems()->size() != 1)
				Assert::Fail();

			col.append(SimpleTestClass("Obj 2"));

			auto it = col.getItems()->begin();
			it++;
			const SimpleTestClass* item2Ptr = &(*it);

			SimpleTestClass::clearMethodCallList();
			col.insert(SimpleTestClass("insertableObj"), item2Ptr);

			if (std::find_if(callsList.begin(), callsList.end(), [&moveConstructorCall] (const std::shared_ptr<BaseCall>& call) -> bool
			{
				return (*call) == moveConstructorCall;
			}) == callsList.end())
			{
				Assert::Fail();
			}


			if (col.getItems()->size() != 3)
				Assert::Fail();

		}
	};
}