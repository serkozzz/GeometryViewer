#pragma once 

#include "ISceneManager.h"


namespace gv
{
	namespace Engine
	{
		class GVAPI SceneManager : public ISceneManager
		{
			static SceneManager* _sharedSceneManager;
			SceneManager();
		public:
			static SceneManager* sharedSceneManager();

			virtual void createMesh(const std::string& meshName, const GeometryData* geometryData);
			virtual void removeMesh(const std::string& meshName);

			virtual ISceneNode* createSceneNode(const std::string& nodeName, const std::string& meshName, const glm::mat4& transform);
			virtual void removeSceneNode(ISceneNode* node);
			virtual void removeSceneNode(const std::string& nodeName);
		};
	}
}