// WinFormView.cpp : main project file.

#include "stdafx.h"

#include "Logger.h"
#include "../gvView/MainView.h"
#include "../gvViewModel/MainViewModel.h"
#include "../gvController/ViewController.h"
#include "../gvModel/Model.h"
#include "../gv3DController/Controller3D.h"


using namespace System::Windows::Forms;


using namespace gv::View;
using namespace gv::Controller;
using namespace gv::Controller3D;
using namespace gv::Model;

//[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	sk::Logger::sharedLogger()->setBehavior(
		std::shared_ptr<sk::IWritingBehavior>(new sk::FileWritingBehavior("geometryViewer.log")));
	sk::Logger::sharedLogger()->writeMessage("--------------------------------------------"
		"------------------------------------------------------------------------------");
	sk::Logger::sharedLogger()->writeMessage("\n\n\n");
	sk::Logger::sharedLogger()->writeMessage("GeometryViewer application has started");
	sk::Logger::sharedLogger()->writeMessage(std::to_string((int)sk::Logger::sharedLogger()));
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Model* model = new Model();
	MainViewModel^ viewModel = gcnew MainViewModel(model->getPlanManager().getPlan());
	MainView^ f = gcnew MainView(viewModel);
	
	Controller3D* controller3D = new Controller3D(model);
	controller3D->create3DView(800, 600);
	Application::Run(f);
	delete controller3D;
	delete model;
	return 0;
}
