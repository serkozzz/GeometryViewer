

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

		TEST_METHOD(getLastErrorsTest)
		{			
			auto errorsCollector = ErrorsCollector::sharedErrorsCollector();
			int errorsNumber = 6;
			for(int i = 0; i < errorsNumber; i++)
			{
				errorsCollector->addError("error" + std::to_string(i));
			}

			auto errors = errorsCollector->getLastErrors(10);

			Assert::AreEqual((int)errors.size(), errorsNumber);
		}

		TEST_METHOD_CLEANUP(CleanUp)
		{

		}
	};
}