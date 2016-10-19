#include "MainWindow.h"

BEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_MENU(wxID_ABOUT, MainWindow::OnAbout)
EVT_TOOL(ID_SETTINGS, MainWindow::OnSettings)
END_EVENT_TABLE()



MainWindow::MainWindow(const wxString & Title, const wxSize & Size): wxFrame(NULL, wxID_ANY, Title, wxDefaultPosition, Size, wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxMINIMIZE_BOX | wxCLIP_CHILDREN)
{
	m_Panel = new wxPanel(this);
	LoadToolbarIcons();
	//m_Menubar = new wxMenuBar;
}


MainWindow::~MainWindow()
{

}

void MainWindow::OnSettings(wxCommandEvent & event)
{
	Settings * settings = new Settings(this, wxT("SweetSnip Settings"), wxDefaultPosition, wxSize(300, 350));
	settings->Show(true);
}

void MainWindow::OnAbout(wxCommandEvent & event)
{
	wxMessageBox(wxT("This program was created by Sweats using wxWidgets"), wxT("About"));
}

void MainWindow::LoadToolbarIcons()
{
	wxImage::AddHandler(new wxPNGHandler);

	m_Toolbar = CreateToolBar();
	//m_Toolbar->AddTool(ID_SNIP_NEW, wxT("New SweetSnip"), wxBitmap(wxT("NewSnip.png"), wxBITMAP_TYPE_PNG), wxT("New SweetSnip"));
	//m_Toolbar->AddTool(ID_SNIP_CLEAR, wxT("Clear SweetSnip"), wxBitmap(wxT("ClearSnip.png"), wxBITMAP_TYPE_PNG), wxT("Clear SweetSnip"));
	m_Toolbar->AddTool(ID_SETTINGS, wxT("SweetSnip Settings"), wxBitmap(wxT("Settings.png"), wxBITMAP_TYPE_PNG), wxT("SweetSnip Settings"));
	m_Toolbar->Realize();
}
	