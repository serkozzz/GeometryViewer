#pragma once 

#include "dllexport.h"

#include <string>
#include <memory>
#include "ISceneNode.h"

namespace gv
{
	namespace Engine
	{
		GVAPI class ISceneManager
		{
		public:
			///Exceptions:
			///if meshName is not unique method throw std::invalid_argument exception 
			virtual void createMesh(const std::string& meshName, const GeometryData* geometryData);

			///Exceptions:
			///if mesh with MeshName is abscent method throw std::invalid_argument exception 
			virtual void removeMesh(const std::string& meshName);

			///Exceptions:
			///if mesh is abscent or nodeName is not unique method throw std::invalid_argument exception 
			virtual ISceneNode* createSceneNode(const std::string& nodeName, const std::string& meshName, const glm::mat4& transform);

			///Exceptions:
			///if node is abscent in the scene method throw std::invalid_argument exception 
			virtual void removeSceneNode(ISceneNode* node);
		
			///Exceptions:
			///if node with nodeName is abscent in the scene method throw std::invalid_argument exception 
			virtual void removeSceneNode(const std::string& nodeName);
		};
	}
}