
#include <glm/gtc/matrix_transform.hpp>

#include "CameraMovingRealizationMatrix.h"
#include "Logger.h"

using namespace gv::Controller3D;


void CameraMovingRealizationMatrix::setCamera(gv::Model::ICamera* camera)
{
	_camera = camera;
}



void CameraMovingRealizationMatrix::moveCamera(float right, float forward)
{
	//_camera->trySetPosition(glm::vec3(0, 0, -1));
	//return;
	glm::vec4 directionVec = -_camera->getTransform()[2];// * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);

	glm::vec4 rightVec = _camera->getTransform()[0]; //* glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);

	glm::vec4 movement = directionVec * forward + rightVec * right;

	//sk::Logger::sharedLogger()->writeMessage("directionVec: " 
	//	+ std::to_string(directionVec.x) + ", "
	//	+ std::to_string(directionVec.y) + ", "
	//	+ std::to_string(directionVec.z) + ", ");

	//sk::Logger::sharedLogger()->writeMessage("rightVec: " 
	//	+ std::to_string(rightVec.x) + ", "
	//	+ std::to_string(rightVec.y) + ", "
	//	+ std::to_string(rightVec.z) + ", ");

	//_camera->trySetTransform(glm::translate(_camera->getTransform(), glm::vec3(movement)));
	_camera->trySetPosition(_camera->getPosition() + glm::vec3(movement));
}



void CameraMovingRealizationMatrix::rotateCamera(float dx, float dy)
{
	glm::mat4 resultTransform = _camera->getTransform();

	glm::vec4 position(resultTransform[3]);
	resultTransform[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	//Oy - dx rotation
	glm::mat4 oyRotation =  glm::rotate(glm::mat4(1.0f), dx, glm::vec3(0.0, 1.0, 0.0));
	resultTransform = oyRotation * resultTransform;

	//Ox - dy rotation
	glm::vec3 right(resultTransform[0]);
	glm::mat4 oxRotation = glm::rotate(glm::mat4(1.0f), dy, right);
	resultTransform = oxRotation * resultTransform;

	normalizeOrthoForMatrix(resultTransform);

	resultTransform[3] = position;
	_camera->trySetTransform(resultTransform);
}

void CameraMovingRealizationMatrix::normalizeOrthoForMatrix(glm::mat4& matrix)
{
	glm::vec3 x(matrix[0]);
	glm::vec3 y(matrix[1]);
	glm::vec3 z(matrix[2]);

	x = glm::normalize(x);
	y = glm::normalize(y);
	z = glm::normalize(glm::cross(x, y));

	x = glm::normalize(glm::cross(y, z));
	y = glm::normalize(glm::cross(z, x));

	matrix[0] = glm::vec4(x, 0);
	matrix[1] = glm::vec4(y, 0);
	matrix[2] = glm::vec4(z, 0);
}