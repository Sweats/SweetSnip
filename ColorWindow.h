#pragma once

#include "Includes.h"

#ifndef COLORWINDOW_H
#define COLORWINDOW_H

class ColorWindow: public wxFrame
{
public:
	ColorWindow(wxWindow * Window, const wxString & Title, const wxSize & Size, wxFileConfig * config, int Option);
	~ColorWindow();

private:
	wxPanel * m_Panel;
	wxPanel * m_Colorpanel;
	wxPanel * m_Redpanel;
	wxPanel * m_Greenpanel;
	wxPanel * m_Bluepanel;
	wxSlider * m_RedSlider;
	wxSlider * m_GreenSlider;
	wxSlider * m_BlueSlider;
	wxButton * m_SaveButton;
	wxFileConfig * m_config; // Passed from the settings window

	void OnRedSliderChanged(wxCommandEvent & event);
	void OnGreenSliderChanged(wxCommandEvent & event);
	void OnBlueSliderChanged(wxCommandEvent & event);
	void OnClose(wxCloseEvent & event);
	void OnSave(wxCommandEvent & event);
	
	void SaveColorSettings();
	void LoadColorSettings(); // Loads into wxcolour depending on what int Option is
	void CheckColors(int & r, int & g, int & b);
	void SetSliderValues();

	// Outline Colors for shape.
	int m_Red_Outline;
	int m_Green_Outline;
	int m_Blue_Outline;
	wxColour m_Outline_Color; // Color of shape outline when drawing rectangle with mouse
	const wxString m_RedKey_Outline = wxT("Shape Outline Color: Red");
	const wxString m_GreenKey_Outline = wxT("Shape Outline Color: Green");
	const wxString m_BlueKey_Outline = wxT("Shape Outline Color: Blue");

// -----------------------------------------------------------------------

	// Shape Colors
	int m_Red_Shape;
	int m_Green_Shape;
	int m_Blue_Shape;
	wxColour m_Shape_Color; //  Color inside the shape itself and its transparency
	const wxString m_RedKey_Shape = wxT("Shape Color: Red");
	const wxString m_GreenKey_Shape = wxT("Shape Color: Green");
	const wxString m_BlueKey_Shape = wxT("Shape Color: Blue");

// -----------------------------------------------------------------------

	// Background Colors.
	int m_Red_Background;
	int m_Green_Background;
	int m_Blue_Background;
	wxColour m_Background_Color; // Color/Transparency everywhere outside the rectangle
	const wxString m_RedKey_Background = wxT("Background Color: Red");
	const wxString m_GreenKey_Background = wxT("Background Color: Green");
	const wxString m_BlueKey_Background = wxT("Background Color: Blue");


 // -----------------------------------------------------------------------

	int m_Option;

	bool m_Changed;

	DECLARE_EVENT_TABLE()
};

enum
{
	ID_SLIDER_RED,
	ID_SLIDER_GREEN,
	ID_SLIDER_BLUE,
	ID_BUTTON_SAVE_COLOR,
};

#endif // !COLORWINDOW_H

