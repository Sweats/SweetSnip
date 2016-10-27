#pragma once

#include "Includes.h"
#include "Settings.h"
#include "DesktopFrame.h"
#include "Taskbar.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


class MainWindow: public wxFrame
{
public:
	MainWindow(const wxString & Title, const wxSize & Size);
	~MainWindow();


private:
	wxPanel * m_Panel;
	wxButton * m_Button;
	wxMenuBar * m_Menubar;
	wxToolBar * m_Toolbar;

	wxMenuBar * m_MenuBar;
	wxMenu * m_menu;

	Taskbar * m_Taskbar;

	int m_option; // for the defines

	bool m_SnipTaken;

	void OnSettings(wxCommandEvent & event);
	void OnAbout(wxCommandEvent & event);
	void OnNewSnip(wxCommandEvent & event);
	void OnMinimize(wxIconizeEvent &  event);
	void OnHotkeyPressed(wxKeyEvent & event);
	void LoadToolbarIcons();
	void LoadSettings();
	void SetHotKey();


	wxString m_HotkeyLetter;
	wxString m_HotkeyModifier;
	bool m_Setting_Minimize;
	wxSize GetScreenResolution();

	DECLARE_EVENT_TABLE()
};

#endif

enum
{
	ID_BUTTON = wxID_HIGHEST + 1,
	ID_SETTINGS,
	ID_SNIP_NEW,
	ID_SNIP_CLEAR,
	ID_SNIP_SAVE,
	ID_SNIP_CANCEL,
	ID_ABOUT,
	ID_HOTKEY,
};

