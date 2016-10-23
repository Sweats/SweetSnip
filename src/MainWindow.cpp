#include "MainWindow.h"

BEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_MENU(wxID_ABOUT, MainWindow::OnAbout)
EVT_TOOL(ID_SETTINGS, MainWindow::OnSettings)
EVT_TOOL(ID_SNIP_NEW, MainWindow::OnNewSnip)
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

void MainWindow::OnNewSnip(wxCommandEvent & event)
{
	wxSize ScreenResolution = GetScreenResolution();

	DesktopFrame * test = new DesktopFrame(this, ScreenResolution);
	test->Show();
	//this->Hide();


	//test->Close(true);
	//this->Show();

	//dc.SetBrush(wxBrush(wxColour(255, 0, 0)))
	//dc.DrawRectangle(20, 40, 200, 200);

	

	//wxSleep(1);
}

void MainWindow::LoadToolbarIcons()
{
	wxImage::AddHandler(new wxPNGHandler);

	m_Toolbar = CreateToolBar(wxTB_DEFAULT_STYLE | wxTB_TEXT);
	m_Toolbar->AddTool(ID_SNIP_NEW, wxT("New SweetSnip"), wxBitmap(wxT("NewSnip.png"), wxBITMAP_TYPE_PNG), wxT("New SweetSnip"));
	//m_Toolbar->AddTool(ID_SNIP_CLEAR, wxT("Clear SweetSnip"), wxBitmap(wxT("ClearSnip.png"), wxBITMAP_TYPE_PNG), wxT("Clear SweetSnip"));
	m_Toolbar->AddTool(ID_SETTINGS, wxT("SweetSnip Settings"), wxBitmap(wxT("Settings.png"), wxBITMAP_TYPE_PNG), wxT("SweetSnip Settings"));
	m_Toolbar->Realize();
}

/*wxBitmap MainWindow::CaptureDesktop(wxScreenDC & dc, int x, int y)
{
	wxBitmap Screenshot(x, y);
	wxMemoryDC memdc;
	memdc.SelectObject(Screenshot);
	memdc.Blit(0, 0, x, y, &dc, 0, 0);
	memdc.SelectObject(wxNullBitmap);
	return Screenshot;
}


void MainWindow::ModifyImage(wxImage & image, int x, int y, int alpha)
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			image.SetRGB(x, y, m_Red_Background, m_Green_Background, m_Blue_Background);
			image.SetAlpha(x, y, alpha);
		}
	}
}
*/

wxSize MainWindow::GetScreenResolution()
{
	wxScreenDC dc;
	return dc.GetSize();
}
	