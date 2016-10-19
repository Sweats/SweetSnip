#pragma once

#include "Includes.h"
#include "Settings.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


class MainWindow: public wxFrame
{
public:
	MainWindow(const wxString & Title);
	~MainWindow();

private:
	wxPanel * m_Panel;
	wxButton * m_Button;
	wxMenuBar * m_Menubar;

	void OnButton(wxCommandEvent & event);
	void OnAbout(wxCommandEvent & event);
	DECLARE_EVENT_TABLE()
};

#endif

enum
{
	ID_BUTTON = wxID_HIGHEST + 1,
};

