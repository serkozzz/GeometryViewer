// WinFormView.cpp : main project file.

#include "stdafx.h"
#include "../gvView/MainForm.h"

using namespace System::Windows::Forms;


using namespace gv::gvView;

//[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	gvView* view = new gvView();
	MainForm^ f = gcnew MainForm(view);
	Application::Run(f);
	return 0;
}
