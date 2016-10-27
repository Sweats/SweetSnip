#include "Taskbar.h"

BEGIN_EVENT_TABLE(Taskbar, wxTaskBarIcon)
EVT_MENU(ID_NEWSNIP, Taskbar::OnNewSnip)
EVT_MENU(ID_QUIT, Taskbar::OnQuitSweetSnip)
EVT_MENU(ID_SHOW, Taskbar::OnShowSweetSnip)
END_EVENT_TABLE()


Taskbar::Taskbar(wxWindow * Window, const wxString & Hotkey): wxTaskBarIcon(), m_Window(Window), m_Hotkey(Hotkey)
{
	this->SetIcon(wxIcon(wxT("SweetSnipIcon.png"), wxBITMAP_TYPE_PNG), wxT("SweetSnip"));
	m_Menu = this->CreatePopupMenu();
}


Taskbar::~Taskbar()
{

}

wxMenu * Taskbar::CreatePopupMenu()
{
	wxMenu * menu = new wxMenu;
	menu->Append(ID_NEWSNIP, wxT("&New Snip\t" + m_Hotkey));
	menu->AppendSeparator();
	menu->Append(ID_SHOW, wxT("&Show SweetSnip"));
	menu->AppendSeparator();
	menu->Append(ID_QUIT, wxT("&Exit SweetSnip"));
	return menu;
}

void Taskbar::OnNewSnip(wxCommandEvent & event)
{
	DesktopFrame * SnippetWindow = new DesktopFrame(m_Window, GetScreenResolution(), DESKTOP_FRAME, true);
	SnippetWindow->Show();
}

void Taskbar::OnQuitSweetSnip(wxCommandEvent & event)
{
	m_Window->Destroy();
}

void Taskbar::OnShowSweetSnip(wxCommandEvent & event)
{
	m_Window->Show();
}

wxSize Taskbar::GetScreenResolution()
{
	wxScreenDC dc;
	return dc.GetSize();
}
