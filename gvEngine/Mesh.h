#pragma once 

#include <string>

namespace gv
{
	namespace Engine
	{
		struct Mesh
		{
			std::string name;
			int pointsNumber;
			int iboOffsetInBytes;
		};
	}
}