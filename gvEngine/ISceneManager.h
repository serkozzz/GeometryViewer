#pragma once 

#include "dllexport.h"

#include <string>
#include <memory>
#include "ISceneNode.h"
#include "GeometryData.h"

namespace gv
{
	namespace Engine
	{
		class GVAPI Camera;
		class GVAPI ISceneManager
		{
		public:

			/*
			Attention!!! geometryData must be valid after "createMesh" call. Not delete this!!!
			Exceptions:
			if meshName is not unique method throw std::invalid_argument exception 
			*/
			virtual void createMesh(const std::string& meshName, std::shared_ptr<const GeometryData> geometryData) = 0;

			/*
			Exceptions:
			if mesh with MeshName is abscent method throw std::invalid_argument exception 
			*/
			virtual void removeMesh(const std::string& meshName) = 0;

			/*
			Exceptions:
			if mesh is abscent or nodeName is not unique method throw std::invalid_argument exception 
			*/
			virtual ISceneNode* createSceneNode(const std::string& nodeName, const std::string& meshName) = 0;
			virtual ISceneNode* createSceneNode(const std::string& nodeName, const std::string& meshName, const glm::mat4& transform) = 0;

			/*
			Exceptions:
			if node is abscent in the scene method throw std::invalid_argument exception 
			*/
			virtual void removeSceneNode(ISceneNode* node) = 0;

			/*
			Exceptions:
			if node with nodeName is abscent in the scene method throw std::invalid_argument exception 
			*/
			virtual void removeSceneNode(const std::string& nodeName) = 0;

			virtual Camera* get3DCamera() const = 0;
		};
	}
}