

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../gvEngine/ErrorsCollector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gv::Engine;



namespace UnitTests
{
	TEST_CLASS(ErrorsCollectorTest)
	{
	public:

		TEST_METHOD_INITIALIZE(Fixture)
		{
		}

		TEST_METHOD(ErrorsCollector_getLastErrorsTest)
		{			
			auto errorsCollector = ErrorsCollector::sharedErrorsCollector();
			const int errorsNumber = 6;
			std::string errorMessages[errorsNumber];
			for(int i = 0; i < errorsNumber; i++)
			{
				errorMessages[i] = "error" + std::to_string(i);
				errorsCollector->addError(errorMessages[i]);
			}

			auto tenErrorsQuery = errorsCollector->getLastErrors(10);
			Assert::AreEqual((int)tenErrorsQuery.size(), errorsNumber);


			auto threeErrorsQuery = errorsCollector->getLastErrors(3);
			auto it = threeErrorsQuery.rbegin();
			Assert::AreEqual(*it++, errorMessages[errorsNumber - 1]);
			Assert::AreEqual(*it++, errorMessages[errorsNumber - 2]);
			Assert::AreEqual(*it++, errorMessages[errorsNumber - 3]);

		}

		TEST_METHOD(ErrorsCollector_getLastErrorTest)
		{	
			auto errorsCollector = ErrorsCollector::sharedErrorsCollector();
			const int errorsNumber = 6;
			std::string errorMessages[errorsNumber];
			for(int i = 0; i < errorsNumber; i++)
			{
				errorMessages[i] = "error" + std::to_string(i);
				errorsCollector->addError(errorMessages[i]);
			}

			Assert::AreEqual(errorsCollector->getLastError(), errorMessages[errorsNumber - 1]);
		}

		TEST_METHOD(ErrorsCollector_getAllErrorsTest)
		{	
			auto errorsCollector = ErrorsCollector::sharedErrorsCollector();
			const int errorsNumber = 50;
			std::string errorMessages[errorsNumber];
			for(int i = 0; i < errorsNumber; i++)
			{
				errorMessages[i] = "error" + std::to_string(i);
				errorsCollector->addError(errorMessages[i]);
			}

			auto allErrors = errorsCollector->getAllErrors();
			auto it = allErrors.rbegin();
			for (int i = 0; i < errorsNumber; i++)
			{
				Assert::AreEqual(*it++, errorMessages[errorsNumber - i - 1]);
			}

		}


		TEST_METHOD_CLEANUP(CleanUp)
		{

		}
	};
}