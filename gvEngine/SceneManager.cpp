#include "SceneManager.h"

using namespace gv::Engine;


SceneManager* SceneManager::_sharedSceneManager = nullptr;

SceneManager::SceneManager()
{

}

SceneManager* SceneManager::sharedSceneManager()
{
	if(!_sharedSceneManager)
	{
		_sharedSceneManager = new SceneManager();
	}
	return _sharedSceneManager;
}


void SceneManager::createMesh(const std::string& meshName, const GeometryData* geometryData)
{

}

void SceneManager::removeMesh(const std::string& meshName)
{

}

ISceneNode* SceneManager::createSceneNode(const std::string& nodeName, const std::string& meshName, const glm::mat4& transform)
{
	return nullptr;
}

void SceneManager::removeSceneNode(ISceneNode* node)
{

}

void SceneManager::removeSceneNode(const std::string& nodeName)
{

}


Camera* SceneManager::get3DCamera() const
{
	return _camera3D.get();
}


void SceneManager::setCurrentCamera(std::shared_ptr<Camera> camera3D)
{
	_camera3D = camera3D;
}