#pragma once

#include <string>

namespace gvModelUnitTests
{	
	enum Method
	{
		planElementPropChangedMethod,
		pointPropChangedMethod,
		planElementTryPropChangedMethod,
		pointTryPropChangedMethod,
		itemAddedEventMethod,
		itemRemovedEventMethod
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

		bool operator!= (const Call& other)
		{
			return !this->operator==(other);
		}

	private:
		Method method;
		std::string propertyName;
	};

	template<typename T>
	struct CallWithValue : public Call
	{
		CallWithValue(Method method, std::string propertyName, const T* value) 
			: Call(method, propertyName), value(value)
		{
		}

		//bool operator== (const CallWithValue<T>& other)
		//{
		//	if (this->method != other.method)
		//		return false;
		//	if (this->propertyName != other.propertyName)
		//		return false;
		//	if (this->value != other.value)
		//		return false;

		//	return true;
		//}
	private:
		const T* value;
	};
}