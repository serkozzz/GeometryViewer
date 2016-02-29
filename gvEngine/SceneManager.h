#pragma once 

#include <map>

#include "ISceneManager.h"
#include "Camera.h"


namespace gv
{
	namespace Engine
	{
		class SceneNode;

		class GVAPI SceneManager : public ISceneManager
		{
			static SceneManager* _sharedSceneManager;
			std::map<std::string, std::shared_ptr<SceneNode> > _nodes;
			std::shared_ptr<Camera> _camera3D;
			SceneManager();
		public:
			static SceneManager* sharedSceneManager();

			virtual void createMesh(const std::string& meshName, const GeometryData* geometryData);
			virtual void removeMesh(const std::string& meshName);

			virtual ISceneNode* createSceneNode(const std::string& nodeName, const std::string& meshName);
			virtual ISceneNode* createSceneNode(const std::string& nodeName, const std::string& meshName, const glm::mat4& transform);
			virtual void removeSceneNode(ISceneNode* node);
			virtual void removeSceneNode(const std::string& nodeName);

			virtual Camera* get3DCamera() const;
			virtual void setCurrentCamera(std::shared_ptr<Camera> Camera3D);

			const std::map<std::string, std::shared_ptr<SceneNode> >& getNodes();

		};
	}
}