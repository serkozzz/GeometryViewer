
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
	glm::vec4 directionVec = _camera->getTransform() * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
	glm::vec4 rightVec = _camera->getTransform() * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);

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
	glm::mat4 resultTransform;

	//Oy - dx rotation
	glm::mat4 upRotation = glm::rotate(_camera->getTransform(), dx, glm::vec3(0.0, 1.0, 0.0));

	//Ox - dy rotation
	glm::vec4 rightVec = _camera->getTransform() * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	glm::mat4 rightRotation = glm::rotate(_camera->getTransform(), dy, glm::vec3(rightVec));

	_camera->trySetTransform(rightRotation);
}