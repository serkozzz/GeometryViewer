
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Controller3D.h"
#include "PrimitiveCreator.h"
#include "../gvEngine/ISceneNode.h"
#include "../gvEngine/ISceneManager.h"
#include "../gvEngine/gvEngineAPI.h"


using namespace gv::Engine;

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
			static int id = 0;
			const GeometryData* geometryData = nullptr;
			if (p->getPrimitive() == PrimitiveType::cubePrimitiveType)
				meshName = _cubeMeshName;
			else if (p->getPrimitive() == PrimitiveType::spherePrimitiveType)
				meshName = _sphereMeshName;

			std::string sceneNodeName = "node_" + std::to_string(id) + "_" + p->getName();
			glm::mat4 transformMatrix(1.0f);
			glm::translate(transformMatrix, p->getPosition());
			ISceneNode* sceneNode = _sceneManager->createSceneNode(sceneNodeName, meshName, transformMatrix);
			if (_points.find(p) != _points.end())
				throw std::exception("Try add point that has been already added");

			_points[p] = sceneNode;
		}


		void Controller3D::pointRemoved(const std::shared_ptr<IPoint>& p)
		{
			if (_points.find(p) == _points.end())
				throw std::exception("Try remove point that is abscent in the Scene");

			_sceneManager->removeSceneNode(_points[p]);
			_points.erase(p);
		}
#pragma endregion Model Events
	}
}