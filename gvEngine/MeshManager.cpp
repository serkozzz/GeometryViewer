


#include "MeshManager.h"
#include "VideoMemoryManager.h"

using namespace gv::Engine;

MeshManager* MeshManager::_meshManagerInstance = nullptr;


MeshManager::MeshManager()
{

}

MeshManager* MeshManager::sharedMeshManager()
{
	if (_meshManagerInstance == nullptr)
		_meshManagerInstance = new MeshManager();
	return _meshManagerInstance;
}


void MeshManager::createMesh(const std::string& meshName, const GeometryData* geometryData)
{
	if (_meshes.find(meshName) != _meshes.end())
	{
		std::string message = "Mesh with name = " + meshName + " is already exist";
		throw std::exception(message.c_str());
	}


	auto& videoMemoryDataDescription = VideoMemoryManager::sharedVideoMemoryManager()->addData(geometryData);
	Mesh mesh;
	mesh.name = meshName;
	mesh.IBOoffset = videoMemoryDataDescription.startPos;
	mesh.pointsNumber = videoMemoryDataDescription.vertexesNumber;
	_meshes[meshName] = mesh;
}


std::shared_ptr<Mesh> MeshManager::getMesh(std::string name)
{
	auto it = _meshes.find(name);
	if (it == _meshes.end())
		return nullptr;
	return std::make_shared<Mesh>(it->second);
}