#include "SceneManager.h"
#include "MeshManager.h"
#include "SceneNode.h"

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


void SceneManager::createMesh(const std::string& meshName, std::shared_ptr<const GeometryData> geometryData)
{
	MeshManager::sharedMeshManager()->createMesh( meshName, geometryData);
}

void SceneManager::removeMesh(const std::string& meshName)
{
}

ISceneNode* SceneManager::createSceneNode(const std::string& nodeName, const std::string& meshName, const glm::mat4& transform)
{
	if (_nodes.find(nodeName) != _nodes.end())
	{
		std::string message = "Node with name = " + nodeName + " is already exist";
		throw std::logic_error(message.c_str());
	}

	std::shared_ptr<Mesh> mesh = MeshManager::sharedMeshManager()->getMesh(meshName);
	if (mesh == nullptr)
	{
		std::string message = "Mesh with name = " + meshName + " is not exist";
		throw std::logic_error(message.c_str());
	}

	std::shared_ptr<SceneNode> node(new SceneNode(nodeName, meshName, transform));
	_nodes[nodeName] = node;
	return node.get();
}

ISceneNode* SceneManager::createSceneNode(const std::string& nodeName, const std::string& meshName)
{
	return createSceneNode(nodeName, meshName, glm::mat4(1.0f));
}

void SceneManager::removeSceneNode(ISceneNode* node)
{
	removeSceneNode(node->getName());
}

void SceneManager::removeSceneNode(const std::string& nodeName)
{
	_nodes.erase(nodeName);
}


Camera* SceneManager::get3DCamera() const
{
	return _camera3D.get();
}


void SceneManager::setCurrentCamera(std::shared_ptr<Camera> camera3D)
{
	_camera3D = camera3D;
}


const std::map<std::string, std::shared_ptr<SceneNode> >& SceneManager::getNodes()
{
	return _nodes;
}