#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <list>
#include <string>
#include <algorithm>
#include <memory>

#include <common.h>
#include <EventHandler/ObserverableCollection.h>

#include <UnitTestUtils/BaseCall.h>
#include <UnitTestUtils/TestClass.h>

using namespace skb::UnitTestUtils;



namespace gvModelUnitTests
{		
	TEST_CLASS(ObserverableCollectionTest)
	{
		template<typename T>
		struct Call : public BaseCall
		{
			Call(int methodType, std::string propertyName, const T& value) 
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
				//todo call of base class operator
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
			const T& value;

		};

		template<typename T>
		class Registrator
		{
			std::shared_ptr<Call<T> > _call;
		public:
			Call<T>* getCall()
			{
				return _call.get();
			}

			void ItemAdded(const skb::ItemAddedEventArgs<T>& arg)
			{
				_call = std::make_shared<Call<int> >(Call<int>::Method_itemAddedEvent, "", arg.item);
			}


			void ItemRemoved(const skb::ItemRemovedEventArgs<T>& arg)
			{
				_call = std::make_shared<Call<int> >(Call<int>::Method_itemRemovedEvent, "", arg.item);
			}
		};

	public:

		TEST_METHOD(AppendTest)
		{
			skb::ObserverableCollection< std::list, int > col;
			Registrator<int> registrator;
			//int subsriptionId = (col.itemAdded  += &registrator.ItemAdded);
			int subsriptionId = (col.itemAdded += std::bind(&Registrator<int>::ItemAdded, &registrator, std::placeholders::_1));

			for (int i = 1; i <= 10; i++)
			{
				int testItem = 11 * i;

				col.push_back(testItem);

				if (col.size() != i || col.back() != testItem)
					Assert::Fail();

				Call<int> requieredCall(Call<int>::Method_itemAddedEvent, "", col.back());
				if (requieredCall != *registrator.getCall())
					Assert::Fail();
			}

			col.itemAdded -= subsriptionId;
		}


		TEST_METHOD(InsertTest)
		{
			skb::ObserverableCollection< std::list, int > col;
			Registrator<int> registrator;
			int subsriptionId = (col.itemAdded += std::bind(&Registrator<int>::ItemAdded, &registrator, std::placeholders::_1));
			int testItem1 = 11;
			int testItem2 = 34;
			int insertableItem = 88;


			col.push_back(testItem1);
			col.push_back(testItem2);


			col.insert(--col.end(), insertableItem);

			auto it = col.begin();
			it++;

			if (col.size() != 3 || *it != insertableItem)
				Assert::Fail();

			Call<int> requierdCall(Call<int>::Method_itemAddedEvent, "", *it);
			if (requierdCall != *registrator.getCall())
				Assert::Fail();

			col.itemAdded -= subsriptionId;
		}


		TEST_METHOD(RemoveTest)
		{
			skb::ObserverableCollection< std::list, int > col;
			Registrator<int> registrator;
			int subsriptionId = (col.itemRemoved += std::bind(&Registrator<int>::ItemRemoved, &registrator, std::placeholders::_1));

			int testItem1 = 11;
			int testItem2 = 34;

			col.push_back(testItem1);
			col.push_back(testItem2);

			int firstItem = col.front();
			col.erase(col.begin());
			Call<int> requierdCall(Call<int>::Method_itemRemovedEvent, "", firstItem);

			if (col.size() != 1 || col.front() != testItem2)
				Assert::Fail();


			if (requierdCall != *registrator.getCall())
				Assert::Fail();
		}


		TEST_METHOD(MoveSemanticsTest)
		{
			skb::ObserverableCollection< std::list, SimpleTestClass > col;

			SimpleTestClass testItem1("Obj 1");
			col.push_back(std::move(testItem1));

			auto callsList = SimpleTestClass::getMethodCallList();
			const BaseCall moveConstructorCall(BaseCall::Method_Move_Constructor);

			if (std::find_if(callsList.begin(), callsList.end(), [&moveConstructorCall] (const std::shared_ptr<BaseCall>& call) -> bool
			{
				return (*call) == moveConstructorCall;
			}) == callsList.end())
			{
				Assert::Fail();
			}


			if (col.size() != 1)
				Assert::Fail();

			col.push_back(SimpleTestClass("Obj 2"));

			auto it = col.begin();
			it++;

			SimpleTestClass::clearMethodCallList();
			col.insert(it, SimpleTestClass("insertableObj"));

			if (std::find_if(callsList.begin(), callsList.end(), [&moveConstructorCall] (const std::shared_ptr<BaseCall>& call) -> bool
			{
				return (*call) == moveConstructorCall;
			}) == callsList.end())
			{
				Assert::Fail();
			}

			if (col.size() != 3)
				Assert::Fail();

		}


		TEST_METHOD(UniquePtrCollection)
		{
			skb::ObserverableCollection<std::list, std::unique_ptr<int>> col;
			{
				for (int i = 1; i < 10; i++)
				{
					col.push_back(std::unique_ptr<int>(new int(i)));
				}

				for (int i = 0; i > -5; i--)
				{
					col.insert(col.begin(), std::unique_ptr<int>(new int(i)));
				}
			}
			auto it = col.begin();
			int i = -4;
			for (it, i; it != col.end(); i++, it++)
			{
				int* value = (*it).get(); 
				if (**it != i)
					Assert::Fail();
			}

		}
	};
}