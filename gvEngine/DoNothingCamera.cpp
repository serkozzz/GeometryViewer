#include "DoNothingCamera.h"
#include <glm/gtc/matrix_transform.hpp>




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
	//float _fov = (3.14f / 3.0f); 
	//float _nearClipDistance = (0.1f);
	//float _farClipDistance = (100.0f);


	//return glm::perspective(
	//	_fov,         // Горизонтальное поле обзора в градусах. Обычно между 90&deg; (очень широкое) и 30&deg; (узкое)
	//	640.0f / 480, // width / height
	//	_nearClipDistance,       
	//	_farClipDistance 
	//	);
}


glm::mat4 DoNothingCamera::getViewProjectMatrix() const
{
	return glm::mat4(1.0f);
	//float _fov = (3.14f / 3.0f); 
	//float _nearClipDistance = (0.1f);
	//float _farClipDistance = (100.0f);


	//return glm::perspective(
	//	_fov,         // Горизонтальное поле обзора в градусах. Обычно между 90&deg; (очень широкое) и 30&deg; (узкое)
	//	640.0f / 480, // width / height
	//	_nearClipDistance,       
	//	_farClipDistance 
	//	);
}