#include "InputListener.h"
#include "Logger.h"
#include "CameraMovingRealizationAngles.h"

using namespace gv;
using namespace gv::Controller3D;

InputListener::InputListener(Model::ICamera* camera)
{
	_cameraMovingRealization.reset(new CameraMovingRealizationAngles());
	_cameraMovingRealization->setCamera(camera);
}

void InputListener::keyPressed(gvKey key) const
{
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

	movement *= 0.1;
	_cameraMovingRealization->moveCamera(movement.x, -movement.y);
}


void InputListener::cursorPositionChanged(double dx, double dy) const
{
	//horizontalAngle += mouseSpeed * deltaTime * float(1024/2 - xpos );
	//verticalAngle   += mouseSpeed * deltaTime * float( 768/2 - ypos );

	_cameraMovingRealization->rotateCamera(dx * 0.01 *(-1), dy * 0.01 *(-1));
	//sk::Logger::sharedLogger()->writeMessage("hAngle = " + std::to_string(_horizontalAngle) + "; vAngle = " + std::to_string(_verticalAngle));

}

