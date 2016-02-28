


#include "MeshManager.h"

using namespace gv::Engine;


void MeshManager::createMesh(const std::string& meshName, const GeometryData* geometryData)
{
	if (_meshes.find(meshName) != _meshes.end())
	{
		std::string message = "Mesh with name = " + meshName + " is already exist";
		throw std::exception(message.c_str());
	}


}


std::shared_ptr<Mesh> MeshManager::getMesh(std::string name)
{
	auto it = _meshes.find(name);
	if (it == _meshes.end())
		return nullptr;
	return std::make_shared<Mesh>(it->second);
}