#include "ColorWindow.h"

BEGIN_EVENT_TABLE(ColorWindow, wxFrame)
EVT_SLIDER(ID_SLIDER_RED, ColorWindow::OnRedSliderChanged)
EVT_SLIDER(ID_SLIDER_GREEN, ColorWindow::OnGreenSliderChanged)
EVT_SLIDER(ID_SLIDER_BLUE, ColorWindow::OnBlueSliderChanged)
EVT_CLOSE(ColorWindow::OnClose)
EVT_BUTTON(ID_BUTTON_SAVE_COLOR, ColorWindow::OnSave)
END_EVENT_TABLE()


ColorWindow::ColorWindow(wxWindow * Window, const wxString & Title, const wxSize & Size, wxFileConfig * config, int Option) : wxFrame(Window, wxID_ANY, Title, wxDefaultPosition, Size, wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN), m_config(config), m_Window(Window)
{
	m_Changed = false;
	m_Option = Option;

	m_Window->Disable();

	m_Panel = new wxPanel(this);
	m_RedSlider = new wxSlider(m_Panel, ID_SLIDER_RED, 0, 0, 255, wxPoint(10, 10), wxSize(255, 20), wxSL_HORIZONTAL | wxSL_LABELS);
	m_GreenSlider = new wxSlider(m_Panel, ID_SLIDER_GREEN, 0, 0, 255, wxPoint(10, 80), wxSize(255, 20), wxSL_HORIZONTAL | wxSL_LABELS);
	m_BlueSlider = new wxSlider(m_Panel, ID_SLIDER_BLUE, 0, 0, 255, wxPoint(10, 150), wxSize(255, 20), wxSL_HORIZONTAL | wxSL_LABELS);
	m_SaveButton = new wxButton(m_Panel, ID_BUTTON_SAVE_COLOR, wxT("No Changes Made"), wxPoint(75, 260), wxSize(120, 40));
	m_Colorpanel = new wxPanel(m_Panel, wxID_ANY, wxPoint(107, 200), wxSize(50, 50));
	m_Redpanel = new wxPanel(m_Panel, wxID_ANY, wxPoint(280, 15), wxSize(15, 15));
	m_Greenpanel = new wxPanel(m_Panel, wxID_ANY, wxPoint(280, 85), wxSize(15, 15));
	m_Bluepanel = new wxPanel(m_Panel, wxID_ANY, wxPoint(280, 155), wxSize(15, 15));
	
	LoadColorSettings();
	SetSliderValues();

	m_SaveButton->Disable();

	//Set Panels
	m_Redpanel->SetBackgroundColour(wxColour(255, 0, 0));
	m_Greenpanel->SetBackgroundColour(wxColour(0, 255, 0));
	m_Bluepanel->SetBackgroundColour(wxColour(0, 0, 255));
}


ColorWindow::~ColorWindow()
{

}

void ColorWindow::OnRedSliderChanged(wxCommandEvent & event)
{
	switch (m_Option)
	{
		case SHAPE_OUTLINE_COLOR:
			m_Red_Outline = m_RedSlider->GetValue();
			m_Outline_Color.Set(m_Red_Outline, m_Green_Outline, m_Blue_Outline);
			m_Colorpanel->SetBackgroundColour(m_Outline_Color);
			break;

		case SHAPE_COLOR:
			m_Red_Shape = m_RedSlider->GetValue();
			m_Shape_Color.Set(m_Red_Shape, m_Green_Shape, m_Blue_Shape);
			m_Colorpanel->SetBackgroundColour(m_Shape_Color);
			break;

		case BACKGROUND_COLOR:
			m_Red_Background = m_RedSlider->GetValue();
			m_Background_Color.Set(m_Red_Background, m_Green_Background, m_Blue_Background);
			m_Colorpanel->SetBackgroundColour(m_Background_Color);
			break;

		default:
			break;
	}

	m_Colorpanel->Refresh();
	m_SaveButton->SetLabelText(wxT("Save Custom Color"));
	m_SaveButton->Enable();
	m_Changed = true;
}

void ColorWindow::OnGreenSliderChanged(wxCommandEvent & event)
{
	switch (m_Option)
	{
		case SHAPE_OUTLINE_COLOR:
			m_Green_Outline = m_GreenSlider->GetValue();
			m_Outline_Color.Set(m_Red_Outline, m_Green_Outline, m_Blue_Outline);
			m_Colorpanel->SetBackgroundColour(m_Outline_Color);
			break;

		case SHAPE_COLOR:
			m_Green_Shape = m_GreenSlider->GetValue();
			m_Shape_Color.Set(m_Red_Shape, m_Green_Shape, m_Blue_Shape);
			m_Colorpanel->SetBackgroundColour(m_Shape_Color);
			break;

		case BACKGROUND_COLOR:
			m_Green_Background = m_GreenSlider->GetValue();
			m_Background_Color.Set(m_Red_Background, m_Green_Background, m_Blue_Background);
			m_Colorpanel->SetBackgroundColour(m_Background_Color);
			break;

		default:
			break;
	}

	m_Colorpanel->Refresh();
	m_SaveButton->SetLabelText(wxT("Save Custom Color"));
	m_SaveButton->Enable();
	m_Changed = true;
}

void ColorWindow::OnBlueSliderChanged(wxCommandEvent & event)
{
	switch (m_Option)
	{
		case SHAPE_OUTLINE_COLOR:
			m_Blue_Outline = m_BlueSlider->GetValue();
			m_Outline_Color.Set(m_Red_Outline, m_Green_Outline, m_Blue_Outline);
			m_Colorpanel->SetBackgroundColour(m_Outline_Color);
			break;
		
		case SHAPE_COLOR:
			m_Blue_Shape = m_BlueSlider->GetValue();
			m_Shape_Color.Set(m_Red_Shape, m_Green_Shape, m_Blue_Shape);
			m_Colorpanel->SetBackgroundColour(m_Shape_Color);
			break;

		case BACKGROUND_COLOR:
			m_Blue_Background = m_BlueSlider->GetValue();
			m_Background_Color.Set(m_Red_Background, m_Green_Background, m_Blue_Background);
			m_Colorpanel->SetBackgroundColour(m_Background_Color);
			break;

		default:
			break;

	}

	m_Colorpanel->Refresh();
	m_SaveButton->SetLabelText(wxT("Save Custom Color"));
	m_SaveButton->Enable();
	m_Changed = true;
}

void ColorWindow::OnSave(wxCommandEvent & event)
{
	m_Changed = false;
	SaveColorSettings();
	m_SaveButton->Disable();
	m_SaveButton->SetLabelText(wxT("Saved Changes"));
}

void ColorWindow::OnClose(wxCloseEvent & event)
{
	if (m_Changed)
	{
		int Response = wxMessageBox(wxT("You have unsaved changes. Do you wish to save them?"), wxT("Warning"), wxYES_NO | wxCANCEL, this);

		if (Response == wxNO)
		{
			Destroy();
		}

		else if (Response == wxYES)
		{
			m_Changed = false;
			SaveColorSettings();
			Destroy();
		}

		else
		{
			return;
		}
	}

	Destroy();
	m_Window->Enable();
}

void ColorWindow::SaveColorSettings()
{
	switch (m_Option)
	{
		case SHAPE_OUTLINE_COLOR:
			m_config->Write(m_RedKey_Outline, m_Red_Outline);
			m_config->Write(m_GreenKey_Outline, m_Green_Outline);
			m_config->Write(m_BlueKey_Outline, m_Blue_Outline);
			break;

		case SHAPE_COLOR:
			m_config->Write(m_RedKey_Shape, m_Red_Shape);
			m_config->Write(m_GreenKey_Shape, m_Green_Shape);
			m_config->Write(m_BlueKey_Shape, m_Blue_Shape);
			break;

		case BACKGROUND_COLOR:
			m_config->Write(m_RedKey_Background, m_Red_Background);
			m_config->Write(m_GreenKey_Background, m_Green_Background);
			m_config->Write(m_BlueKey_Background, m_Blue_Background);
			break;

		default:
			break;
	}
}

// Loads into wxcolour depending on what int Option is
void ColorWindow::LoadColorSettings()
{
	switch (m_Option)
	{
		case SHAPE_OUTLINE_COLOR:
			m_config->Read(m_RedKey_Outline, &m_Red_Outline);
			m_config->Read(m_GreenKey_Outline, &m_Green_Outline);
			m_config->Read(m_BlueKey_Outline, &m_Blue_Outline);
			CheckColors(m_Red_Outline, m_Green_Outline, m_Blue_Outline);
			m_Outline_Color.Set(m_Red_Outline, m_Green_Outline, m_Blue_Outline);
			break;

		case SHAPE_COLOR:
			m_config->Read(m_RedKey_Shape, &m_Red_Shape);
			m_config->Read(m_GreenKey_Shape, &m_Green_Shape);
			m_config->Read(m_BlueKey_Shape, &m_Blue_Shape);
			CheckColors(m_Red_Shape, m_Green_Shape, m_Blue_Shape);
			m_Shape_Color.Set(m_Red_Shape, m_Green_Shape, m_Blue_Shape);
			break;
		
		case BACKGROUND_COLOR:
			m_config->Read(m_RedKey_Background, &m_Red_Background);
			m_config->Read(m_GreenKey_Background, &m_Green_Background);
			m_config->Read(m_BlueKey_Background, &m_Blue_Background);
			CheckColors(m_Red_Background, m_Green_Background, m_Blue_Background);
			m_Background_Color.Set(m_Red_Background, m_Green_Background, m_Blue_Background);
			break;

		default:
			break;
	}
}

// This makes sure manual changes to the config file don't go over 255 because undefined behavior could result
void ColorWindow::CheckColors(int & r, int & g, int & b)
{
	if (r > 255)
	{
		r = 255;
	}

	if (g > 255)
	{
		g = 255;
	}

	if (b > 255)
	{
		b = 255;
	}
}

void ColorWindow::SetSliderValues()
{
	switch (m_Option)
	{
		case SHAPE_OUTLINE_COLOR:
			m_RedSlider->SetValue(m_Red_Outline);
			m_GreenSlider->SetValue(m_Green_Outline);
			m_BlueSlider->SetValue(m_Blue_Outline);
			m_Colorpanel->SetBackgroundColour(m_Outline_Color);
			break;

		case SHAPE_COLOR:
			m_RedSlider->SetValue(m_Red_Shape);
			m_GreenSlider->SetValue(m_Green_Shape);
			m_BlueSlider->SetValue(m_Blue_Shape);
			m_Colorpanel->SetBackgroundColour(m_Shape_Color);
			break;

		case BACKGROUND_COLOR:
			m_RedSlider->SetValue(m_Red_Background);
			m_GreenSlider->SetValue(m_Green_Background);
			m_BlueSlider->SetValue(m_Blue_Background);
			m_Colorpanel->SetBackgroundColour(m_Background_Color);
			break;

		default:
			break;
	}
}