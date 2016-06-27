#pragma once

#include <string>

#include <UnitTestUtils\BaseCall.h>

namespace gvModelUnitTests
{	

	struct Call : public skb::UnitTestUtils::BaseCall
	{	
		enum
		{
			Method_planElementPropChanged,
			Method_pointPropChanged,
			Method_planElementTryPropChanged,
			Method_pointTryPropChanged,
		};


		Call(int methodType, std::string propertyName)
			: BaseCall(methodType), methodType(methodType), propertyName(propertyName)
		{
		}


		bool operator== (const Call& other)
		{
			if (this->methodType != other.methodType)
				return false;
			if (this->propertyName != other.propertyName)
				return false;

			return true;
		}

	private:
		int methodType;
		std::string propertyName;
	};
}