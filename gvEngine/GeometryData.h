#pragma once


#include <list>
#include <glm/glm.hpp>

namespace gv
{
	namespace Engine
	{
		GVAPI struct Vertex
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 uv;
		};


		GVAPI struct GeometryData
		{
			std::list<Vertex> verticies;
			std::list<unsigned int> indecies;
		};
	}
}