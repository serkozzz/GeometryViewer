
#include <algorithm>

#include "PrimitiveCreator.h"
#include "PrimitivesGeometry.h"

using namespace gv;
using namespace gv::Engine;
using namespace gv::Controller3D;


static GeometryData* CreateCube()
{
	static GeometryData* result = new GeometryData();
	for(int i = 0; i < cube_n_points; i++)
	{
		Vertex vertex;
		vertex.position = cube_points[i];
		vertex.normal = cube_normals[i];
		result->verticies.push_back(vertex);
	}
	result->indecies.insert(result->indecies.begin(), cube_indecies, (&cube_indecies[cube_n_indecies]));
	//std::for_each(cube_indecies, &(cube_indecies[cube_n_indecies]) + 1, [result] (int index) 
	//{
	//	result->indecies.push_back(index);
	//});
	return result;
}


static GeometryData* CreateTriangle()
{
	//test triangle
	static GeometryData* triangle = new GeometryData();
	triangle->verticies.push_back(gv::Engine::Vertex(
		glm::vec3(-1.0f, -1.0f, 0.0f),  
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f)));

	triangle->verticies.push_back(gv::Engine::Vertex(
		glm::vec3(1.0f, -1.0f, 0.0f),  
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f)));

	triangle->verticies.push_back(gv::Engine::Vertex(
		glm::vec3(0.0f,  1.0f, 0.0f),  
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f)));


	triangle->indecies.push_back(0);
	triangle->indecies.push_back(1);
	triangle->indecies.push_back(2);
	return triangle;
}

static gv::Engine::GeometryData* CreateSphere()
{
	throw std::exception("NotImplementedException");
}


std::shared_ptr<const GeometryData> PrimitiveCreator::getCube()
{
	return std::shared_ptr<const GeometryData>(CreateCube());
}

std::shared_ptr<const GeometryData> PrimitiveCreator::getSphere()
{
	return std::shared_ptr<const GeometryData>(CreateSphere());
}


std::shared_ptr<const GeometryData> PrimitiveCreator::getTriangle()
{
	return std::shared_ptr<const GeometryData>(CreateTriangle());
}



