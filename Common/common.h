#pragma once



namespace gv
{
	template <typename T>
	class Identifier
	{
		T _id;

	public:
		Identifier(T value): _id(value)
		{
		}

		bool operator== (const Identifier& other)
		{
			if(_id == other._id)
				return true;
			return false;
		}

		bool operator!= (const Identifier& other)
		{
			return !this.operator==(other);
		}
	};



	enum PrimitiveType
	{
		cubePrimitiveType = 0,
		spherePrimitiveType
	};
}