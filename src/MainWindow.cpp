#include "MainWindow.h"

BEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_MENU(wxID_ABOUT, MainWindow::OnAbout)
EVT_TOOL(ID_SETTINGS, MainWindow::OnSettings)
EVT_TOOL(ID_SNIP_NEW, MainWindow::OnNewSnip)
EVT_ICONIZE(MainWindow::OnMinimize)
EVT_HOTKEY(ID_HOTKEY, MainWindow::OnHotkeyPressed)
END_EVENT_TABLE()


MainWindow::MainWindow(const wxString & Title, const wxSize & Size): wxFrame(NULL, wxID_ANY, Title, wxDefaultPosition, Size, wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxMINIMIZE_BOX | wxCLIP_CHILDREN)
{
	m_Panel = new wxPanel(this);
	LoadToolbarIcons();
	LoadSettings();
	m_Taskbar = new Taskbar(this, (m_HotkeyModifier + " + " + m_HotkeyLetter));
	this->SetIcon(wxIcon(wxT("SweetSnipIcon.png"), wxBITMAP_TYPE_PNG));
}


MainWindow::~MainWindow()
{
	this->UnregisterHotKey(ID_HOTKEY);
	delete m_Taskbar;
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

	DesktopFrame * SnippetWindow = new DesktopFrame(this, ScreenResolution, DESKTOP_FRAME, false);
	SnippetWindow->Show();
}

void MainWindow::LoadToolbarIcons()
{
	wxImage::AddHandler(new wxPNGHandler);

	m_Toolbar = CreateToolBar(wxTB_DEFAULT_STYLE | wxTB_TEXT);
	m_Toolbar->AddTool(ID_SNIP_NEW, wxT("&New SweetSnip"), wxBitmap(wxT("NewSnip.png"), wxBITMAP_TYPE_PNG), wxT("New SweetSnip"));
	//m_Toolbar->AddTool(ID_SNIP_CLEAR, wxT("Clear SweetSnip"), wxBitmap(wxT("ClearSnip.png"), wxBITMAP_TYPE_PNG), wxT("Clear SweetSnip"));
	m_Toolbar->AddTool(ID_SETTINGS, wxT("SweetSnip Settings"), wxBitmap(wxT("Settings.png"), wxBITMAP_TYPE_PNG), wxT("SweetSnip Settings"));
	m_Toolbar->Realize();
}

void MainWindow::OnMinimize(wxIconizeEvent & event)
{
	if (event.IsIconized())
	{
		this->Hide();
		const wxString MinimizeNotifyKey = wxT("Notify user when program is minimized");
		wxFileConfig Config(wxEmptyString, wxEmptyString, wxT("Settings.ini"), wxT("Settings.ini"), wxCONFIG_USE_RELATIVE_PATH);
		Config.Read(MinimizeNotifyKey, &m_Setting_Minimize);

		if (m_Setting_Minimize)
		{
			wxNotificationMessage MinimizeMessage(wxT("Notice"), wxT("SweetSnip has been minimized. Press " + m_HotkeyModifier + " + " + m_HotkeyLetter + " to take a snip at any time"), this);
			MinimizeMessage.Show();
		}
	}
}

void MainWindow::OnHotkeyPressed(wxKeyEvent & event)
{
	if (wxWindow::FindWindowById(DESKTOP_FRAME))
	{
		return;
	}

	DesktopFrame * SnippetWindow = new DesktopFrame(this, GetScreenResolution(), DESKTOP_FRAME, true);
	SnippetWindow->Show();
}

wxSize MainWindow::GetScreenResolution()
{
	wxScreenDC dc;
	return dc.GetSize();
}

void MainWindow::LoadSettings()
{
	if (!wxFileName::Exists(wxT("Settings.ini")))
	{
		m_Setting_Minimize = true;
		m_HotkeyLetter = "E";
		m_HotkeyModifier = "CTRL";
		this->RegisterHotKey(ID_HOTKEY,	wxMOD_CONTROL, 'E');
	}

	else
	{
		const wxString m_HotkeyModifierKey = wxT("Hotkey Modifier");
		const wxString m_HotkeyLetterKey = wxT("Hotkey Letter");
		wxFileConfig Config(wxEmptyString, wxEmptyString, wxT("Settings.ini"), wxT("Settings.ini"), wxCONFIG_USE_RELATIVE_PATH);
		Config.Read(m_HotkeyModifierKey, &m_HotkeyModifier);
		Config.Read(m_HotkeyLetterKey, &m_HotkeyLetter);
		SetHotKey();
	}
}

void MainWindow::SetHotKey()
{
	int Modifier = 0;

	if (!m_HotkeyModifier.empty() && !m_HotkeyLetter.empty())
	{
		if (m_HotkeyModifier == "SHIFT")
		{
			Modifier = wxMOD_SHIFT;
		}

		else if (m_HotkeyModifier == "ALT")
		{
			Modifier = wxMOD_ALT;
		}

		else if (m_HotkeyModifier == "CTRL")
		{
			Modifier = wxMOD_CONTROL;
		}

		#ifdef _WIN32 // RegisterHotKey always fails under non-MSW platforms.
		if (!this->RegisterHotKey(ID_HOTKEY, Modifier, m_HotkeyLetter.at(0)))
		{
			wxMessageBox(wxT("The hotkey that was previously saved is not usable because the system already has this hotkey set. Please pick a different one"), wxT("Warning"));
		}
		#endif	
	}
}
	