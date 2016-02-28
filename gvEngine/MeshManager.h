#pragma once 

#include <map>
#include <string>
#include <memory>

#include "GeometryData.h"
#include "Mesh.h"

namespace gv
{
	namespace Engine
	{
		class MeshManager
		{
			std::map<std::string, Mesh> _meshes;

		public:
			void createMesh(const std::string& meshName, const GeometryData* geometryData);
			std::shared_ptr<Mesh> getMesh(std::string name);
		};
	}
}