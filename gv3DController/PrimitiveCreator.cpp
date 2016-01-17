
#include <algorithm>

#include "PrimitiveCreator.h"
#include "PrimitivesGeometry.h"

using namespace gv;
using namespace gv::Engine;
using namespace gv::Controller3D;


static GeometryData* CreateCube()
{
	GeometryData* result = new GeometryData();
	for(int i = 0; i < cube_n_points; i++)
	{
		Vertex vertex;
		vertex.position = cube_points[i];
		vertex.normal = cube_normals[i];
		result->verticies.push_back(vertex);
	}
	result->indecies.insert(result->indecies.begin(), cube_indecies, (&cube_indecies[cube_n_indecies]) + 1);
	//std::for_each(cube_indecies, &(cube_indecies[cube_n_indecies]) + 1, [result] (int index) 
	//{
	//	result->indecies.push_back(index);
	//});
	return result;
}

static gv::Engine::GeometryData* CreateSphere()
{
	throw std::exception("NotImplementedException");
}


const GeometryData* PrimitiveCreator::getCube()
{
	return CreateCube();
}

const GeometryData* PrimitiveCreator::getSphere()
{
	return CreateSphere();
}


