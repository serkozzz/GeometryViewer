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
		_fov,         // �������������� ���� ������ � ��������. ������ ����� 90&deg; (����� �������) � 30&deg; (�����)
		aspect, // width / height
		_nearClipDistance,       
		_farClipDistance 
		);

	glm::vec4 points[20];
	for (int i = 0; i < 20; i++)
	{
		points[i].x = 0;
		points[i].y = 0;
		points[i].z = i - 9;
	}

	glm::vec4 resultPoints[20];
	for (int i = 0; i < 20; i++)
	{
		resultPoints[i] = (_projectionMatrix * points[i]) / points[i].z;
	}

	for (int i = 0; i < 20; i++)
	{
		sk::Logger::sharedLogger()->writeMessage("z = " + std::to_string(points[i].z) + "\t z`= " + std::to_string(resultPoints[i].z));
	}



	float f = _farClipDistance;
	float n = _nearClipDistance;

	_projectionMatrix = glm::mat4(-1.0f / (tan(_fov / 2) * _aspect), 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f / tan(_fov / 2), 0.0f, 0.0f, 
		0.0f, 0.0f, (f + n) / (f - n), 1.0f,
		0.0f, 0.0f, -2 * f * n / (f - n), 0.0f);




}

void Camera::setFOV(float fov)
{
	_fov = fov;
}


glm::mat4 Camera::getViewMatrix() const
{
	// �������� ������� = 1 / �������� �������
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