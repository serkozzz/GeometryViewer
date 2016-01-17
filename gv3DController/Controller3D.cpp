
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Controller3D.h"
#include "PrimitiveCreator.h"
#include "InputController.h"

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
			/////_sceneManager->createMesh(_sphereMeshName, PrimitiveCreator::getSphere());

			auto mCamera = plan->getCamera();
			cameraPropChangedSubscription =
				(mCamera->propertyChanged += std::bind(&Controller3D::cameraPropertyChanged, this, std::placeholders::_1));


			_inputController = new InputController();

		}

		Controller3D::~Controller3D()
		{
			if (_inputController)
				delete _inputController;
		}

		void Controller3D::create3DView()
		{
			Engine::createWindow(800, 600, _inputController);
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
			_pointsSubscriptions[p] = 
				(p->propertyChanged += std::bind(&Controller3D::pointPropertyChanged, this, std::placeholders::_1));
		}


		void Controller3D::pointRemoved(const std::shared_ptr<IPoint>& p)
		{
			if (_points.find(p) == _points.end())
				throw std::exception("Try remove point that is abscent in the Scene");

			p->propertyChanged -= _pointsSubscriptions[p];
			_sceneManager->removeSceneNode(_points[p]);
			_points.erase(p);
		}


		void Controller3D::pointPropertyChanged(const PointPropChangedArgs& args)
		{
			std::shared_ptr<const IPoint> pPtr = std::shared_ptr<const IPoint>(args.sender);

			auto it = _points.find(pPtr);
			if (it == _points.end())
				throw std::exception("Attemption to change point property for point that is abscent in the plan");

			//if (args.propName == IPoint::namePropertyName)
			//{
			//	const std::string* newName = static_cast<const std::string*>(args.newValue);
			//	(*it)->setName(*newName);
			//}
			else if (args.propName == IPoint::positionPropertyName)
			{
				const glm::vec3* newPos = static_cast<const glm::vec3*>(args.newValue);
				it->second->setPosition(pPtr->getPosition());
			}
			else if (args.propName == IPoint::primitivePropertyName)
			{
				const PrimitiveType* newPrimitiveType = static_cast<const PrimitiveType*>(args.newValue);
				std::string meshName;
				const GeometryData* geometryData = nullptr;
				if (*newPrimitiveType == PrimitiveType::cubePrimitiveType)
					meshName = _cubeMeshName;
				else if (*newPrimitiveType == PrimitiveType::spherePrimitiveType)
					meshName = _sphereMeshName;
				it->second->setMesh(meshName);
			}
		}


		void Controller3D::cameraPropertyChanged(const Model::CameraPropChangedArgs& args)
		{
			//TODO change 3d camera
		}

#pragma endregion Model Events
	}
}