#include "CameraMovingRealizationAngles.h"

using namespace gv::Controller3D;

void CameraMovingRealizationAngles::setCamera(gv::Model::ICamera* camera)
{
	_camera = camera;
	_horizontalAngle = 0;
	_verticalAngle = 0;
}



void CameraMovingRealizationAngles::moveCamera(float right, float forward)
{
	glm::vec3 cameraDirection = glm::normalize(getDirection());
	glm::vec3 cameraRight = glm::normalize(getRight());
	glm::vec3 oldPosition = _camera->getPosition();

	glm::vec3 newPos = oldPosition + cameraRight * right + cameraDirection * forward;
	_camera->trySetPosition(newPos);
}


void CameraMovingRealizationAngles::rotateCamera(float dx, float dy)
{
	_horizontalAngle += dx;
	_verticalAngle += dy;
	_camera->trySetTransform(getCameraTransform());
}


glm::mat4 CameraMovingRealizationAngles::getCameraTransform() const
{
	glm::vec3 direction = getDirection();

	glm::vec3 right = getRight();

	glm::vec3 up = glm::cross( right, direction );

	glm::mat4 currentCameraTransform = _camera->getTransform();

	glm::mat4 cameraTransform(glm::vec4(right, 0.0f),
		glm::vec4(up, 0.0f),
		glm::vec4(direction, 0.0f), 
		currentCameraTransform[3]);
	return cameraTransform;
}

glm::vec3 CameraMovingRealizationAngles::getDirection() const
{
	glm::vec3 direction(
		cos(_verticalAngle) * sin(_horizontalAngle),
		sin(_verticalAngle),
		cos(_verticalAngle) * cos(_horizontalAngle)
		);
	return direction;
}

glm::vec3 CameraMovingRealizationAngles::getRight() const
{
	glm::vec3 right = glm::vec3(
		sin(_horizontalAngle - 3.14f/2.0f),
		0,
		cos(_horizontalAngle - 3.14f/2.0f)
		);
	return right;
}
