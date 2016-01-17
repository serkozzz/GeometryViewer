#include "stdafx.h"
#include "CppUnitTest.h"

#include "../gvView/IView.h"
#include "../gvController/ViewController.h"
#include "../gvModel/Model.h"
#include "../gvModel/mPlan.h"
#include "MockView.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace gv::View;
using namespace gv::Controller;
using namespace gv::Model;


namespace UnitTests
{
	TEST_CLASS(ModelTest)
	{

		// Create the main window and run it
		MockView* _view;
		Model* _model;
		ViewController* _viewController;


	public:

		TEST_METHOD_INITIALIZE(Fixture)
		{
			_view = new MockView();
			_model = new Model();
			_viewController = new ViewController(_view, _model);
		}

		TEST_METHOD(AddElementsTest)
		{			
			gv::Model::mPlan* plan = _model ->getPlanManager().getPlanRegerenceForTest();

			_view->emulateAddPointClick(vPoint("point1", glm::vec3(0, 1, 2), gv::PrimitiveType::cubePrimitiveType));
			Assert::AreEqual((int)plan->getPoints().size(), 1);
			Assert::AreEqual((int)_view->_vPoints.size(), 1);
		}

		TEST_METHOD_CLEANUP(CleanUp)
		{
			delete _viewController;
			delete _view;
			delete _model;
		}
	};
}