#pragma once

#include "glm/glm.hpp"

namespace gv
{
	struct Transform
	{
		glm::vec3 position;
		
		/*order - Z, X, Y (all rotations in the parent coordinate system)*/
		glm::vec3 rotationEuler; 
		
		glm::vec3 scale;
	};
}