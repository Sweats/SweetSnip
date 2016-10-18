#include "MainWindow.h"

BEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_MENU(wxID_ABOUT, MainWindow::OnAbout)
EVT_BUTTON(ID_BUTTON, MainWindow::OnButton)
END_EVENT_TABLE()



MainWindow::MainWindow(const wxString & Title): wxFrame(NULL, wxID_ANY, Title)
{
	m_Panel = new wxPanel(this);
	m_Button = new wxButton(m_Panel, ID_BUTTON, wxT("Settings"), wxPoint(100, 100), wxSize(100, 100));
	//m_Menubar = new wxMenuBar;

}


MainWindow::~MainWindow()
{

}

void MainWindow::OnButton(wxCommandEvent & event)
{
	Settings * settings = new Settings(this, wxT("SweetSnip Settings"), wxDefaultPosition, wxSize(300, 350));
	m_Button->Disable();
	settings->Show(true);
}

void MainWindow::OnAbout(wxCommandEvent & event)
{
	wxMessageBox(wxT("This program was created by Sweats using wxWigits"), wxT("About"));
}
