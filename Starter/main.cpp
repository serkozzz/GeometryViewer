// WinFormView.cpp : main project file.

#include "stdafx.h"
#include "../gvView/MainForm.h"
#include "../gvController/ViewController.h"
#include "../gvModel/Model.h"

using namespace System::Windows::Forms;


using namespace gv::View;
using namespace gv::Controller;
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
	Application::Run(f);
	delete viewController;
	delete view;
	delete model;
	return 0;
}
