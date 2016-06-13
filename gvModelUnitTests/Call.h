#pragma once

#include <string>

namespace gvModelUnitTests
{	
	enum Method
	{
		planElementPropChangedMethod,
		pointPropChangedMethod,
		planElementTryPropChangedMethod,
		pointTryPropChangedMethod
	};

	struct Call
	{	
		Call(Method method, std::string propertyName)
			: method(method), propertyName(propertyName)
		{
		}

		Call(const Call& other)
		{
			this->method = other.method;
			this->propertyName = other.propertyName;
		}

		const Call& operator= (const Call& other)
		{
			this->method = other.method;
			this->propertyName = other.propertyName;
			return *this;
		}


		bool operator== (const Call& other)
		{
			if (this->method != other.method)
				return false;
			if (this->propertyName != other.propertyName)
				return false;

			return true;
		}

	private:
		Method method;
		std::string propertyName;
	};
}