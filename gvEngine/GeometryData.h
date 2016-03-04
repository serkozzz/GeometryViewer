#pragma once
#include "dllexport.h"

#include <list>
#include <glm/glm.hpp>

namespace gv
{
	namespace Engine
	{
		struct Vertex
		{
			Vertex(glm::vec3& position, glm::vec3 normal, glm::vec2 uv) 
				: position(position), normal(normal), uv (uv)
			{}

			Vertex()
			{}

			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 uv;
		};


		struct GeometryData
		{
			std::list<Vertex> verticies;
			std::list<unsigned int> indecies;
		};
	}
}