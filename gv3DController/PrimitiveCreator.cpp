
#include <algorithm>

#include "PrimitiveCreator.h"
#include "PrimitivesGeometry.h"

using namespace gv;
using namespace gv::Engine;
using namespace gv::Controller3D;






static GeometryData* createGeometryData(int pointsNumber, 
										int indexiesNumber,
										const glm::vec3* points, 
										const glm::vec3* normals, 
										const unsigned int* indexes)
{
	GeometryData* result = new GeometryData();
	for(int i = 0; i < pointsNumber; i++)
	{
		Vertex vertex;
		vertex.position = points[i];
		vertex.normal = normals[i];
		result->verticies.push_back(vertex);
	}
	result->indecies.insert(result->indecies.begin(), indexes, (&indexes[indexiesNumber]));
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
		glm::vec3(0.0f, -1.0f, 0.0f),  
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


static GeometryData* CreateLittleTriangle()
{
	//test triangle
	static GeometryData* triangle = new GeometryData();
	triangle->verticies.push_back(gv::Engine::Vertex(
		glm::vec3(-1.0f, 0.0f, 0.0f),  
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f)));

	triangle->verticies.push_back(gv::Engine::Vertex(
		glm::vec3(1.0f, 0.0f, 0.0f),  
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



static GeometryData* CreateRectangle(glm::vec2 leftBottom, glm::vec2 rightUp)
{
	//test rectangle
	GeometryData* rectangle = new GeometryData();
	rectangle->verticies.push_back(gv::Engine::Vertex(
		glm::vec3(leftBottom.x, leftBottom.y, 0.0f),  
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f)));

	rectangle->verticies.push_back(gv::Engine::Vertex(
		glm::vec3(leftBottom.x, rightUp.y, 0.0f),  
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec2(0.0f, 1.0f)));

	rectangle->verticies.push_back(gv::Engine::Vertex(
		glm::vec3(rightUp.x,  rightUp.y, 0.0f),  
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f)));

	rectangle->verticies.push_back(gv::Engine::Vertex(
		glm::vec3(rightUp.x,  leftBottom.y, 0.0f),  
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f)));

	rectangle->indecies.push_back(0);
	rectangle->indecies.push_back(3);
	rectangle->indecies.push_back(1);

	rectangle->indecies.push_back(3);
	rectangle->indecies.push_back(2);
	rectangle->indecies.push_back(1);

	return rectangle;
}

std::shared_ptr<const GeometryData> PrimitiveCreator::getBox(glm::vec2 leftBottom, glm::vec2 rightUp, float zExtrudion)
{
	static const int box_n_points = 24;
	static const int box_n_indexies = 36;

	glm::vec3 box_points[box_n_points] = {
		glm::vec3( leftBottom.x, leftBottom.y, 0),
		glm::vec3( leftBottom.x, rightUp.y, 0),
		glm::vec3( rightUp.x, rightUp.y, 0),
		glm::vec3( rightUp.x, leftBottom.y, 0),
		glm::vec3( rightUp.x, leftBottom.y, zExtrudion),
		glm::vec3( leftBottom.x, leftBottom.y, zExtrudion),
		glm::vec3( leftBottom.x, rightUp.y, zExtrudion),
		glm::vec3( rightUp.x, rightUp.y, zExtrudion),
		glm::vec3( leftBottom.x, leftBottom.y, 0),
		glm::vec3( rightUp.x, leftBottom.y, 0),
		glm::vec3( leftBottom.x, leftBottom.y, 0),
		glm::vec3( leftBottom.x, leftBottom.y, zExtrudion),
		glm::vec3( leftBottom.x, rightUp.y, 0),
		glm::vec3( rightUp.x, leftBottom.y, 0),
		glm::vec3( rightUp.x, rightUp.y, 0),
		glm::vec3( rightUp.x, leftBottom.y, zExtrudion),
		glm::vec3( leftBottom.x, rightUp.y, 0),
		glm::vec3( leftBottom.x, rightUp.y, zExtrudion),
		glm::vec3( rightUp.x, rightUp.y, zExtrudion),
		glm::vec3( rightUp.x, rightUp.y, 0),
		glm::vec3( leftBottom.x, leftBottom.y, zExtrudion),
		glm::vec3( rightUp.x, leftBottom.y, zExtrudion),
		glm::vec3( rightUp.x, rightUp.y, zExtrudion),
		glm::vec3( leftBottom.x, rightUp.y, zExtrudion) 
	};


	static glm::vec3 box_normals[box_n_points] = {
		glm::vec3(  0.0,  0.0, -1.0),
		glm::vec3(  0.0,  0.0, -1.0),
		glm::vec3(  0.0,  0.0, -1.0),
		glm::vec3(  0.0,  0.0, -1.0),
		glm::vec3(  0.0, -1.0,  0.0),
		glm::vec3(  0.0, -1.0,  0.0),
		glm::vec3( -1.0,  0.0,  0.0),
		glm::vec3(  1.0,  0.0,  0.0),
		glm::vec3(  0.0, -1.0,  0.0),
		glm::vec3(  0.0, -1.0,  0.0),
		glm::vec3( -1.0,  0.0,  0.0),
		glm::vec3( -1.0,  0.0,  0.0),
		glm::vec3( -1.0,  0.0,  0.0),
		glm::vec3(  1.0,  0.0,  0.0),
		glm::vec3(  1.0,  0.0,  0.0),
		glm::vec3(  1.0,  0.0,  0.0),
		glm::vec3(  0.0,  1.0,  0.0),
		glm::vec3(  0.0,  1.0,  0.0),
		glm::vec3(  0.0,  1.0,  0.0),
		glm::vec3(  0.0,  1.0,  0.0),
		glm::vec3(  0.0,  0.0,  1.0),
		glm::vec3(  0.0,  0.0,  1.0),
		glm::vec3(  0.0,  0.0,  1.0),
		glm::vec3(  0.0,  0.0,  1.0) 
	};


	static unsigned int box_indecies[box_n_indexies] = {
		0,  1,  2,
		2,  3,  0,
		8,  9,  4,
		4,  5,  8,
		10, 11,  6,
		6, 12, 10,
		13, 14,  7,
		7, 15, 13,
		16, 17, 18,
		18, 19, 16,
		20, 21, 22,
		22, 23, 20 
	};

	return std::shared_ptr<const GeometryData>(createGeometryData(
		box_n_points, 
		box_n_indexies,
		box_points,
		box_normals,
		box_indecies));
}




static gv::Engine::GeometryData* CreateSphere()
{
	throw std::exception("NotImplementedException");
}


std::shared_ptr<const GeometryData> PrimitiveCreator::getCube()
{
	return std::shared_ptr<const GeometryData>(createGeometryData(cube_n_points, 
		cube_n_indecies,
		cube_points,
		cube_normals,
		cube_indecies));
}

std::shared_ptr<const GeometryData> PrimitiveCreator::getSphere()
{
	return std::shared_ptr<const GeometryData>(CreateSphere());
}


std::shared_ptr<const GeometryData> PrimitiveCreator::getTriangle()
{
	return std::shared_ptr<const GeometryData>(CreateTriangle());
}

std::shared_ptr<const GeometryData> PrimitiveCreator::getLittleTriangle()
{
	return std::shared_ptr<const GeometryData>(CreateLittleTriangle());
}



std::shared_ptr<const gv::Engine::GeometryData> PrimitiveCreator::getXYRectangle(
	glm::vec2 leftBottom, glm::vec2 rightUp)
{
	return std::shared_ptr<const GeometryData>(CreateRectangle(leftBottom, rightUp));
}


