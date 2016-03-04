


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


void MeshManager::createMesh(const std::string& meshName, std::shared_ptr<const GeometryData> geometryData)
{
	if (_meshes.find(meshName) != _meshes.end())
	{
		std::string message = "Mesh with name = " + meshName + " is already exist";
		throw std::exception(message.c_str());
	}

	Mesh& mesh = _meshes[meshName]; // it creates new mesh and give me ref to this mesh
	mesh.name = meshName;
	VideoMemoryManager::sharedVideoMemoryManager()->addData(geometryData, 
		[&] (VideoMemoryManager::VideoMemoryDescriptor& descriptor) 
	{
		mesh.IBOoffset = descriptor.startPos;
		mesh.pointsNumber = descriptor.vertexesNumber;
	});
}


std::shared_ptr<Mesh> MeshManager::getMesh(std::string name)
{
	auto it = _meshes.find(name);
	if (it == _meshes.end())
		return nullptr;
	return std::make_shared<Mesh>(it->second);
}