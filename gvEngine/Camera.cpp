#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

using namespace gv::Engine;



Camera::Camera(const std::string& name, float aspect) 
	: SceneNode(name), 
	_aspect(aspect),
	_fov(60.0f), 
	_nearClipDistance(0.1f),
	_farClipDistance(100.0f)
{
	_transformMatrix = glm::mat4(1.0f);
	_projectionMatrix = glm::perspective(
		3.14f / 3.0f,         // �������������� ���� ������ � ��������. ������ ����� 90&deg; (����� �������) � 30&deg; (�����)
		aspect, // width / height
		_nearClipDistance,       
		_farClipDistance 
		);
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
	return _projectionMatrix;
}

glm::mat4 Camera::getViewProjectMatrix() const
{

	return getProjectMatrix() * getViewMatrix();
}