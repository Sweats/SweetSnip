#pragma once

#include "Includes.h"
#include "Settings.h"
#include "DesktopFrame.h"

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

	int m_option; // for the defines

	void OnSettings(wxCommandEvent & event);
	void OnAbout(wxCommandEvent & event);
	void OnNewSnip(wxCommandEvent & event);
	void LoadToolbarIcons();
	void LoadColors(wxScreenDC & dc);
	void LoadSettings();
	//void ModifyImage(wxImage & image, int x, int y, int alpha);
	wxSize GetScreenResolution();

	//wxBitmap CaptureDesktop(wxScreenDC & dc, int x, int y);

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
};

