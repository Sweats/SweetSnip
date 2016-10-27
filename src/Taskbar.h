#pragma once

#include "Includes.h"
#include "DesktopFrame.h"

#ifndef TASKBAR_H
#define TASKBAR_H

class Taskbar: public wxTaskBarIcon
{
public:
	Taskbar(wxWindow * Window, const wxString & Hotkey);
	~Taskbar();

private:
	virtual wxMenu * CreatePopupMenu();
	wxMenu * m_Menu;
	wxWindow * m_Window;
	wxString m_Hotkey;
	void OnNewSnip(wxCommandEvent & event);
	void OnQuitSweetSnip(wxCommandEvent & event);
	void OnShowSweetSnip(wxCommandEvent & event);
	wxSize GetScreenResolution();
	DECLARE_EVENT_TABLE()

};

enum
{
	ID_QUIT,
	ID_SHOW,
	ID_NEWSNIP,
};

#endif // !TASKBAR_H

