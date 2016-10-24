#pragma once

#include "Includes.h"

#ifndef TRANSPARENCYWINDOW_H
#define TRANSPARENCYWINDOW_H

class TransparencyWindow: public wxFrame
{
public:
	TransparencyWindow(wxWindow * parent, const wxString & Title, const wxSize & Size, wxFileConfig * config);
	~TransparencyWindow();

private:
	wxPanel * m_Panel;
	wxPanel * m_TransparentPanel;
	wxSlider * m_Slider;
	wxButton * m_SaveChangesButton;
	int m_Transparency;
	wxWindow * m_Window;
	wxFileConfig * m_Config;
	void OnSliderMoved(wxCommandEvent & event);
	void OnSaveChanges(wxCommandEvent & event);
	void OnClose(wxCloseEvent & event);
	void LoadSettings();
	void CheckTransparency();
	bool m_Changed;
	DECLARE_EVENT_TABLE()
};

enum
{
	ID_SLIDER,
	ID_SAVE,
};

#endif // TRANSPARENCYWINDOW_H

