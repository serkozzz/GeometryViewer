#pragma once

#include "CallsDispatcher.h"


namespace skb
{	
	namespace UnitTestUtils
	{

		class SimpleTestClass : public CallsDispatcher
		{
			char* buffer;
		public:
			SimpleTestClass(const char* str) : buffer(new char[strlen(str) + 1])
			{
				strcpy(buffer, str);
				CallsDispatcher::addCall(std::make_shared<BaseCall>(BaseCall::Method_Default_Constructor));
			}

			~SimpleTestClass()
			{
				delete[] buffer;
				CallsDispatcher::addCall(std::make_shared<BaseCall>(BaseCall::Method_Destructor));
			}

			SimpleTestClass(const SimpleTestClass& other) : buffer(new char[strlen(other.buffer) + 1])
			{
				strcpy(buffer, other.buffer);
				CallsDispatcher::addCall(std::make_shared<BaseCall>(BaseCall::Method_Copy_Constructor));
			}


			//TODO swap
			SimpleTestClass(SimpleTestClass&& other)
			{
				buffer = other.buffer;
				other.buffer = nullptr;
				CallsDispatcher::addCall(std::make_shared<BaseCall>(BaseCall::Method_Move_Constructor));
			}


			void operator=(SimpleTestClass other)
			{
				std::swap(this->buffer, other.buffer);
				CallsDispatcher::addCall(std::make_shared<BaseCall>(BaseCall::Method_By_Value_Assignment_Operator));
			}

		};
	}
}