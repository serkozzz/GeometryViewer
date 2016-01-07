#pragma once

#include <string>
#include <glm/glm.hpp>
#include "../Common/common.h"

using namespace glm;

namespace gv
{

	struct vPointData
	{
		vec3 position;
		std::string name;
		Primitive primitive;
		std::string id;
	};

}