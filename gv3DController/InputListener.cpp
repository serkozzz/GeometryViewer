#include "InputListener.h"
#include "Logger.h"


using namespace gv;
using namespace gv::Controller3D;

InputListener::InputListener(Model::ICamera* camera)
	: _camera(camera)
{
	_horizontalAngle = 0;
	_verticalAngle = 0;
}

void InputListener::keyPressed(gvKey key) const
{
	glm::vec3 cameraDirection = glm::normalize(getDirection());
	glm::vec3 cameraRight = glm::normalize(getRight());
	glm::vec2 movement(0, 0);
	float delta = 1;
	switch(key)
	{
	case gvKey::GV_KEY_UP:
		{
			movement.y = delta;
			break;
		}
	case gvKey::GV_KEY_DOWN:
		{
			movement.y -= delta;
			break;
		}
	case gvKey::GV_KEY_LEFT:
		{
			movement.x -= delta;
			break;
		}
	case gvKey::GV_KEY_RIGHT:
		{
			movement.x += delta;
			break;
		}
	}
	
	glm::vec3 oldPosition = _camera->getPosition();
	movement *= 0.1;
	glm::vec3 newPos = oldPosition + cameraRight * movement.x + (-cameraDirection) * movement.y;

	_camera->trySetPosition(newPos);
}


void InputListener::cursorPositionChanged(double dx, double dy) const
{
	//horizontalAngle += mouseSpeed * deltaTime * float(1024/2 - xpos );
	//verticalAngle   += mouseSpeed * deltaTime * float( 768/2 - ypos );

	_horizontalAngle += dx * 0.01 *(-1);
	_verticalAngle += dy * 0.01 *(-1);
	_camera->trySetTransform(getCameraTransform());
	//sk::Logger::sharedLogger()->writeMessage("hAngle = " + std::to_string(_horizontalAngle) + "; vAngle = " + std::to_string(_verticalAngle));

}

glm::mat4 InputListener::getCameraTransform() const
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

glm::vec3 InputListener::getDirection() const
{
	glm::vec3 direction(
		cos(_verticalAngle) * sin(_horizontalAngle),
		sin(_verticalAngle),
		cos(_verticalAngle) * cos(_horizontalAngle)
		);
	return direction;
}

glm::vec3 InputListener::getRight() const
{
	glm::vec3 right = glm::vec3(
		sin(_horizontalAngle - 3.14f/2.0f),
		0,
		cos(_horizontalAngle - 3.14f/2.0f)
		);
	return right;
}