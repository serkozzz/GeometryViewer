#include "stdafx.h"
#include "CppUnitTest.h"

#include "../EventHandler.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	namespace EventHandlerTest
	{

		class EventArgs
		{
		public:
			EventArgs(std::string message, int count) : _message(message), _count(count)
			{
			}
			std::string getMessage()
			{
				return _message;
			}

			int getCount()
			{
				return _count;
			}

		private:
			std::string _message;
			int _count;
		};



		class MockView
		{
		public:
			MockView()
			{}

			void emulateClick(EventArgs args)
			{
				if(btnClickEvent != nullptr)
					btnClickEvent(args);
			}

			EventHandler<EventArgs> btnClickEvent;
		};



		class MockPresenter
		{
			MockView& _view;
			int _subscriptionId;

		public:
			MockPresenter(MockView& form) : _view(form), _args("", 0)
			{
				subscribe();
			}

			void onBtnClick(EventArgs args)
			{
				_args = args; //for check if event was catched
			}

			void subscribe()
			{
				_subscriptionId = (_view.btnClickEvent += std::bind(&MockPresenter::onBtnClick, this, std::placeholders::_1)); 
			}

			void unsubscribe()
			{
				_view.btnClickEvent -= _subscriptionId;
			}

			EventArgs _args;   //for check if event was catched
		};




		TEST_CLASS(EventHandlerTest)
		{
		public:
			TEST_CLASS_INITIALIZE(Fixture)
			{

			}

			TEST_METHOD(NullPtrTest)
			{
				MockView view;
				if(view.btnClickEvent != nullptr)
					Assert::Fail();

				MockPresenter p1(view);

				if(view.btnClickEvent == nullptr)
					Assert::Fail();

				MockPresenter p2(view);

				p1.unsubscribe();
				if(view.btnClickEvent == nullptr)
					Assert::Fail();

				p2.unsubscribe();
				if(view.btnClickEvent != nullptr)
					Assert::Fail();

			}

			TEST_METHOD(EventHandlingTest)
			{
				MockView view;
				MockPresenter p1(view);
				MockPresenter p2(view);

				//first event
				{
					view.emulateClick(EventArgs("first", 1));
					Assert::AreEqual(p1._args.getCount(), 1);
					Assert::AreEqual(p1._args.getMessage().c_str(), "first");
					Assert::AreEqual(p2._args.getCount(), 1);
					Assert::AreEqual(p2._args.getMessage().c_str(), "first");
				}
				//repeat event
				{
					view.emulateClick(EventArgs("second", 2));
					Assert::AreEqual(p1._args.getCount(), 2);
					Assert::AreEqual(p1._args.getMessage().c_str(), "second");
					Assert::AreEqual(p2._args.getCount(), 2);
					Assert::AreEqual(p2._args.getMessage().c_str(), "second");
				}
				//unsubscribe check
				{
					p1.unsubscribe();
					view.emulateClick(EventArgs("third", 3));
					Assert::AreNotEqual(p1._args.getCount(), 3);
					Assert::AreNotEqual(p1._args.getMessage().c_str(), "third");

					Assert::AreEqual(p2._args.getCount(), 3);
					Assert::AreEqual(p2._args.getMessage().c_str(), "third");
				}
				//repeat subscription check
				{
					p1.subscribe();
					view.emulateClick(EventArgs("4th", 4));
					Assert::AreEqual(p1._args.getCount(), 4);
					Assert::AreEqual(p1._args.getMessage().c_str(), "4th");

					Assert::AreEqual(p2._args.getCount(), 4);
					Assert::AreEqual(p2._args.getMessage().c_str(), "4th");
				}
			}

			TEST_CLASS_CLEANUP(CleanUp)
			{
				int c = 12;
				c++;
			}
		};
	}
}