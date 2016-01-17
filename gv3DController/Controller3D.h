#pragma once


#include <map>
#include <memory>

#include "../gvModel/Model.h"
#include "../gvModel/ICamera.h"
#include "IPoint.h"

namespace gv
{
	namespace Engine
	{
		class ISceneNode;
		class ISceneManager;

	}

	namespace Controller3D
	{
		class InputController;

		class Controller3D
		{
		private:
			Model::Model* _model;
			Model::PlanManager& _planManager;
			InputController* _inputController;
			Engine::ISceneManager* _sceneManager;
			std::map<std::shared_ptr<const IPoint>, Engine::ISceneNode* > _points;
			std::map<std::shared_ptr<const IPoint>, int > _pointsSubscriptions;

			int pointAddedSubscription;
			int pointRemovedSubscription;
			int cameraPropChangedSubscription;


			void pointAdded(const std::shared_ptr<IPoint>& p);
			void pointRemoved(const std::shared_ptr<IPoint>& p);
			void pointPropertyChanged(const PointPropChangedArgs& args);

			void cameraPropertyChanged(const Model::CameraPropChangedArgs& args);

			const std::string _cubeMeshName;
			const std::string _sphereMeshName;	
		public:
			Controller3D(Model::Model* model);
			~Controller3D();
			void create3DView();
		};
	}
}