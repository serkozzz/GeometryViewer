#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Logger.h"

using namespace gv::Engine;



Camera::Camera(const std::string& name, float aspect) 
	: SceneNode(name), 
	_aspect(aspect),
	_fov(3.14f / 3.0f), 
	_nearClipDistance(0.1f),
	_farClipDistance(100.0f)
{
	_transformMatrix = glm::mat4(1.0f);
	_projectionMatrix = glm::perspective(
		_fov,         // Горизонтальное поле обзора в градусах. Обычно между 90&deg; (очень широкое) и 30&deg; (узкое)
		aspect, // width / height
		_nearClipDistance,       
		_farClipDistance 
		);


	
	float f = _farClipDistance;
	float n = _nearClipDistance;

	//_projectionMatrix = glm::mat4(1.0f / (tan(_fov / 2) * _aspect), 0.0f, 0.0f, 0.0f,
	//	0.0f, 1.0f / tan(_fov / 2), 0.0f, 0.0f, 
	//	0.0f, 0.0f, (f + n) / (f - n), 1.0f,
	//	0.0f, 0.0f, -2 * f * n / (f - n), 0.0f);



	glm::vec4 points[20];
	for (int i = 0; i < 20; i++)
	{
		points[i].x = 1;
		points[i].y = 1;
		points[i].z = i - 9;

		if(points[i].z == 0)
			points[i].z = 0.2f;

		points[i].w = 1;
	}

	glm::vec4 resultPoints[20];
	for (int i = 0; i < 20; i++)
	{
		resultPoints[i] = (_projectionMatrix * points[i]);
		resultPoints[i] /= resultPoints[i].w;
	}

	sk::Logger::sharedLogger()->clear();
	sk::Logger::sharedLogger()->writeMessage("--------------------------------------------------------------------------------------------------------------------------");
	for (int i = 0; i < 20; i++)
	{	
		sk::Logger::sharedLogger()->writeMessage("x = " + std::to_string(points[i].x) + "\t x`= " + std::to_string(resultPoints[i].x));
		sk::Logger::sharedLogger()->writeMessage("y = " + std::to_string(points[i].y) + "\t y`= " + std::to_string(resultPoints[i].y));
		sk::Logger::sharedLogger()->writeMessage("z = " + std::to_string(points[i].z) + "\t z`= " + std::to_string(resultPoints[i].z));
		sk::Logger::sharedLogger()->writeMessage("");
	}







}

void Camera::setFOV(float fov)
{
	_fov = fov;
}


glm::mat4 Camera::getViewMatrix() const
{
	// обратная матрица = 1 / исходная матрица
	return glm::inverse(_transformMatrix);
}

glm::mat4 Camera::getProjectMatrix() const
{
	//return glm::mat4(1.0f);
	return _projectionMatrix;
}

glm::mat4 Camera::getViewProjectMatrix() const
{

	return getProjectMatrix() * getViewMatrix();
}