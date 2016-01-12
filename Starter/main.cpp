// WinFormView.cpp : main project file.

#include "stdafx.h"
#include "../gvView/MainForm.h"
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
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	gvView* view = new gvView();
	Model* model = new Model();
	MainForm^ f = gcnew MainForm(view);
	ViewController* viewController = new ViewController(view, model);
	Controller3D* controller3D = new Controller3D(model);
	Application::Run(f);
	delete controller3D;
	delete viewController;
	delete view;
	delete model;
	return 0;
}
