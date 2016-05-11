#include "DoNothingCamera.h"





using namespace gv::Engine;


DoNothingCamera::DoNothingCamera(const std::string& name, float aspect) : Camera(name, aspect)
{

}


glm::mat4 DoNothingCamera::getViewMatrix() const 
{
	return glm::mat4(1.0f);
}


glm::mat4 DoNothingCamera::getProjectMatrix() const
{
	return glm::mat4(1.0f);
}


glm::mat4 DoNothingCamera::getViewProjectMatrix() const
{
	return glm::mat4(1.0f);
}