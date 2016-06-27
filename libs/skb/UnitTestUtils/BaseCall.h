#pragma once



namespace skb
{	
	namespace UnitTestUtils
	{
		struct BaseCall
		{
		public:

			BaseCall(int methodType) : methodType(methodType)
			{

			}

			bool operator == (const BaseCall& other)
			{
				return this->methodType == other.methodType;
			}

			bool operator != (const BaseCall& other)
			{
				return !(*this == other);
			}

			enum
			{
				Method_Default_Constructor,
				Method_Destructor,
				Method_Copy_Constructor,
				Method_Move_Constructor,
				Method_Copy_Assignment_Operator,
				Method_Move_Assignment_Operator,
				Method_By_Value_Assignment_Operator
			};

			int methodType;
		};
	}
}


