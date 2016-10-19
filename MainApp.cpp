#include "MainApp.h"
#include "MainWindow.h"

IMPLEMENT_APP(MainApp)

MainApp::MainApp()
{
}


MainApp::~MainApp()
{
}

bool MainApp::OnInit()
{
	MainWindow * Window = new MainWindow(wxT("SweetSnip"));
	Window->Show(true);
	return true;
}
