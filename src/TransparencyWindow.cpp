#include "TransparencyWindow.h"

BEGIN_EVENT_TABLE(TransparencyWindow, wxFrame)
EVT_SLIDER(ID_SLIDER, TransparencyWindow::OnSliderMoved)
EVT_BUTTON(ID_SAVE, TransparencyWindow::OnSaveChanges)
EVT_CLOSE(TransparencyWindow::OnClose)
END_EVENT_TABLE()

TransparencyWindow::TransparencyWindow(wxWindow * parent, const wxString & Title, const wxSize & Size, wxFileConfig * config): wxFrame(parent, wxID_ANY, Title, wxDefaultPosition, Size, wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN), m_Config(config), m_Window(parent)
{
	m_Changed = false;
	LoadSettings();
	this->SetIcon(wxIcon(wxT("RGB.png"), wxBITMAP_TYPE_PNG));

	m_Panel = new wxPanel(this);
	m_Slider = new wxSlider(m_Panel, ID_SLIDER, 0, 0, 255, wxPoint(10, 20), wxSize(255, 20), wxSL_HORIZONTAL | wxSL_LABELS | wxSL_INVERSE);
	m_SaveChangesButton = new wxButton(m_Panel, ID_SAVE, wxT("No Changes Made"), wxPoint(85, 130), wxSize(120, 40));
	m_TransparentPanel = new wxPanel(m_Panel, wxID_ANY, wxPoint(117, 70), wxSize(50, 50));

	parent->Disable();
	m_TransparentPanel->SetBackgroundColour(wxColour(m_Transparency, m_Transparency, m_Transparency));
	m_Slider->SetValue(m_Transparency);
	m_SaveChangesButton->Disable();
}


TransparencyWindow::~TransparencyWindow()
{

}

void TransparencyWindow::OnSliderMoved(wxCommandEvent & event)
{
	m_Changed = true;
	m_Transparency = m_Slider->GetValue();
	m_TransparentPanel->SetBackgroundColour(wxColour(m_Transparency, m_Transparency, m_Transparency));
	m_SaveChangesButton->SetLabelText(wxT("Save Changes"));
	m_SaveChangesButton->Enable();
	m_TransparentPanel->Refresh();
}

void TransparencyWindow::OnSaveChanges(wxCommandEvent & event)
{
	const wxString TransparencyKey = wxT("Shape Transparency:");
	m_Changed = false;
	m_SaveChangesButton->Disable();
	m_SaveChangesButton->SetLabelText(wxT("Saved Changes"));
	m_Config->Write(TransparencyKey, m_Transparency);
}

void TransparencyWindow::OnClose(wxCloseEvent & event)
{
	if (m_Changed)
	{
		int Response = wxMessageBox(wxT("You have unsaved changes. Do you wish to save them?"), wxT("Warning"), wxYES_NO | wxCANCEL | wxICON_QUESTION, this);

		if (Response == wxNO)
		{
			Destroy();
		}

		else if (Response == wxYES)
		{
			const wxString TransparencyKey = wxT("Shape Transparency:");
			m_Changed = false;
			// Save Setting
			m_Config->Write(TransparencyKey, m_Transparency);
			this->Destroy();
		}

		else
		{
			return;
		}
	}

	this->Destroy();
	m_Window->Enable();
	m_Window->Show();
}

void TransparencyWindow::LoadSettings()
{
	const wxString TransparencyKey = wxT("Shape Transparency:");
	m_Config->Read(TransparencyKey, &m_Transparency);
	CheckTransparency();
}

void TransparencyWindow::CheckTransparency()
{
	if (m_Transparency > 255)
	{
		m_Transparency = 255;
	}
}
