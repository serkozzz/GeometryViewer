

#include "Controller3D.h"
#include "PrimitiveCreator.h"
#include "../gvEngine/ISceneNode.h"
#include "../gvEngine/ISceneManager.h"
#include "../gvEngine/gvEngineAPI.h"


namespace gv
{
	namespace Controller3D
	{
		Controller3D::Controller3D(Model::Model* model)
			: _model(model), 
			_planManager(model->getPlanManager()),
			_cubeMeshName("Cube"),
			_sphereMeshName("Sphere")
		{
			//model events
			auto plan = _planManager.getPlan();
			pointAddedSubscription =
				(plan->pointAdded += std::bind(&Controller3D::pointAdded, this, std::placeholders::_1));
			pointRemovedSubscription = 
				(plan->pointRemoved += std::bind(&Controller3D::pointRemoved, this, std::placeholders::_1));

			_sceneManager = Engine::getSceneManager();
			_sceneManager->createMesh(_cubeMeshName, PrimitiveCreator::getCube());
			//_sceneManager->createMesh(_sphereMeshName, PrimitiveCreator::getSphere());
		}

#pragma region Model Events
		void Controller3D::pointAdded(const std::shared_ptr<IPoint>& p)
		{
			std::string meshName;
			const Engine::GeometryData* geometryData = nullptr;
			if (p->getPrimitive() == PrimitiveType::cubePrimitiveType)
				meshName = _cubeMeshName;
			else if (p->getPrimitive() == PrimitiveType::spherePrimitiveType)
				meshName = _sphereMeshName;

			//_sceneManager->createSceneNode("", meshName, 
		}


		void Controller3D::pointRemoved(const std::shared_ptr<IPoint>& p)
		{
			
		}
#pragma endregion Model Events
	}
}