#pragma once


#include <map>
#include <memory>

#include "../gvModel/Model.h"
#include "IPoint.h"

namespace gv
{
	namespace Engine
	{
		class ISceneNode;
		class ISceneManager;
	}
}

namespace gv
{
	namespace Controller3D
	{
		class Controller3D
		{
		private:
			Model::Model* _model;
			Model::PlanManager& _planManager;
			Engine::ISceneManager* _sceneManager;
			std::map<std::shared_ptr<IPoint>, Engine::ISceneNode* > _points;

			const std::string _cubeMeshName;
			const std::string _sphereMeshName;		

			void pointAdded(const std::shared_ptr<IPoint>& p);
			void pointRemoved(const std::shared_ptr<IPoint>& p);

			int pointAddedSubscription;
			int pointRemovedSubscription;
		public:
			Controller3D(Model::Model* model);
		};
	}
}