#pragma once


#include <glm/glm.hpp>


// Geometry of the cube.
static const int cube_n_points = 24;
static const int cube_n_triangles = 12;
static const int cube_n_indecies = cube_n_triangles *3;
static const int cube_size = 100;

static glm::vec3 cube_points[cube_n_points] = {
	glm::vec3( -0.5, -0.5, -0.5),
	glm::vec3( -0.5,  0.5, -0.5),
	glm::vec3(  0.5,  0.5, -0.5),
	glm::vec3(  0.5, -0.5, -0.5),
	glm::vec3(  0.5, -0.5,  0.5),
	glm::vec3( -0.5, -0.5,  0.5),
	glm::vec3( -0.5,  0.5,  0.5),
	glm::vec3(  0.5,  0.5,  0.5),
	glm::vec3( -0.5, -0.5, -0.5),
	glm::vec3(  0.5, -0.5, -0.5),
	glm::vec3( -0.5, -0.5, -0.5),
	glm::vec3( -0.5, -0.5,  0.5),
	glm::vec3( -0.5,  0.5, -0.5),
	glm::vec3(  0.5, -0.5, -0.5),
	glm::vec3(  0.5,  0.5, -0.5),
	glm::vec3(  0.5, -0.5,  0.5),
	glm::vec3( -0.5,  0.5, -0.5),
	glm::vec3( -0.5,  0.5,  0.5),
	glm::vec3(  0.5,  0.5,  0.5),
	glm::vec3(  0.5,  0.5, -0.5),
	glm::vec3( -0.5, -0.5,  0.5),
	glm::vec3(  0.5, -0.5,  0.5),
	glm::vec3(  0.5,  0.5,  0.5),
	glm::vec3( -0.5,  0.5,  0.5) 
};

static glm::vec3 cube_normals[cube_n_points] = {
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

static unsigned int cube_indecies[cube_n_triangles * 3] = {
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