#include "Settings.h"

BEGIN_EVENT_TABLE(Settings, wxFrame)
EVT_CLOSE(Settings::OnClose)

// General Settings Checkboxes

EVT_CHECKBOX(ID_CHECKBOX_CLIPBOARD, Settings::OnClipboardChanged)
EVT_CHECKBOX(ID_CHECKBOX_SAVE_FILE, Settings::OnSaveFileCheckboxChanged)
EVT_CHECKBOX(ID_CHECKBOX_PLAY_SOUND, Settings::OnPlaySoundCheckboxChanged)

// General Settings Buttons

EVT_BUTTON(ID_BUTTON_SAVE, Settings::OnSaveSettings)
EVT_BUTTON(ID_BUTTON_SET_FILE_LOCATION, Settings::OnSetFilePath)
EVT_BUTTON(ID_BUTTON_SET_SOUND_PATH, Settings::OnPlaySoundFilePath)
EVT_BUTTON(ID_BUTTON_PLAY_SOUND, Settings::OnPlaySoundButton)


// Color Settings Checkboxes

EVT_CHECKBOX(ID_CHECKBOX_USE_OUTLINE_COLOR, Settings::OnUseOutlineColorCheckbox)
EVT_CHECKBOX(ID_CHECKBOX_USE_SHAPE_COLOR, Settings::OnUseShapeColorCheckbox)
EVT_CHECKBOX(ID_CHECKBOX_USE_BACKGROUND_COLOR, Settings::OnUseBackgroundColorCheckbox)

// Color Settings Buttons

EVT_BUTTON(ID_BUTTON_PICK_OUTLINE_COLOR, Settings::OnPickOutlineColorButton)
EVT_BUTTON(ID_BUTTON_PICK_SHAPE_COLOR, Settings::OnPickShapeColorButton)
EVT_BUTTON(ID_BUTTON_PICK_BACKGROUND_COLOR, Settings::OnPickBackgroundColorButton)

// MISC

EVT_TOOL(ID_TOOLBAR_GENERAL_SETTINGS, Settings::OnLoadGeneralSettings)
EVT_TOOL(ID_TOOLBAR_COLOR_SETTINGS, Settings::OnLoadColorSettings)
END_EVENT_TABLE()

Settings::Settings(wxWindow * window, const wxString & Title, const wxPoint & Point, const wxSize & Size): wxFrame(window, wxID_ANY, Title, Point, Size, wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
	m_Panel = new wxPanel(this);

	SetupToolbars();

	m_Changed = false;

	m_config = new wxFileConfig(wxEmptyString, wxEmptyString, wxT("Settings.ini"), wxT("Settings.ini"), wxCONFIG_USE_RELATIVE_PATH);


	if (!wxFileName::Exists(wxT("Settings.ini")))
	{
		CreateSettings();
	}

	else
	{
		LoadSettings();
	}

	AllocateControls();
	LoadGeneralSettingsLayout();
	UpdateGUISettings();

	m_Save->Disable();
}


Settings::~Settings()
{
	delete m_config;
}

void Settings::OnClose(wxCloseEvent & event)
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
			SaveSettings();
			Destroy();
		}

		else
		{
			return;
		}
	}
	
	Destroy();
}

void Settings::OnSaveSettings(wxCommandEvent & event)
{
	m_Changed = false;
	SaveSettings();
	m_Save->Disable();
	m_Save->SetLabel(wxT("Saved Changes"));
}

void Settings::OnClipboardChanged(wxCommandEvent & event)
{
	m_Changed = true;
	m_Save->Enable();
	m_Save->SetLabel(wxT("Save Changes"));

	if (event.IsChecked())
	{
		m_Setting_CopyToClipboard = true;
	}

	else
	{
		m_Setting_CopyToClipboard = false;
	}
}

void Settings::OnSetFilePath(wxCommandEvent & event)
{
	wxDirDialog ImageLocation(this, wxT("Select a location to save your images"), wxEmptyString, wxDD_DEFAULT_STYLE);

	if (ImageLocation.ShowModal() == wxID_OK)
	{
		m_ImageFilePath = ImageLocation.GetPath();

		if (!m_ImageFilePath.empty())
		{
			m_Changed = true;
			m_Save->Enable();
			m_Save->SetLabel(wxT("Save Changes"));
		}
	}
}

void Settings::OnSaveFileCheckboxChanged(wxCommandEvent & event)
{
	m_Changed = true;
	m_Save->Enable();
	m_Save->SetLabel(wxT("Save Changes"));

	if (event.IsChecked())
	{
		m_SaveFileLocation->Enable();
		m_Setting_SaveImages = true;
	}

	else
	{
		m_SaveFileLocation->Disable();
		m_Setting_SaveImages = false;
	}
}

void Settings::OnPlaySoundCheckboxChanged(wxCommandEvent & event)
{
	m_Changed = true;

	m_Save->Enable();
	m_Save->SetLabel(wxT("Save Changes"));

	if (event.IsChecked())
	{
		m_Setting_PlaySound = true;

		if (!m_SoundFilePath.empty())
		{
			m_PlaySoundButton->Enable();
		}

		m_PlaySoundPath->Enable();
	}

	else
	{
		m_PlaySoundPath->Disable();
		m_PlaySoundButton->Disable();
		m_Setting_PlaySound = false;
	}
}

void Settings::OnPlaySoundFilePath(wxCommandEvent & event)
{
	wxFileDialog FileExplorer(this, wxT("Choose a sound file that plays when you capture an image"), wxEmptyString, wxEmptyString, wxT("WAV Files (*.wav)|*.wav"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (FileExplorer.ShowModal() == wxID_OK)
	{
		m_SoundFilePath = FileExplorer.GetPath();

		if (!m_SoundFilePath.empty())
		{
			m_Save->Enable();
			m_Save->SetLabel(wxT("Save Changes"));
			m_Changed = true;
		}

	}
}

void Settings::OnPlaySoundButton(wxCommandEvent & event)
{
	wxSound Sound;

	Sound.Create(wxT("‪C:\\Users\\Sweats\\Desktop\\click_x.wav"), true);

	if (Sound.IsOk())
	{
		//wxMessageBox("Sound loaded successfully!");
		Sound.Play(wxSOUND_ASYNC);
	}

	else
	{
		wxMessageBox("Sound not loaded successfully!");
	}
}

void Settings::OnUseOutlineColorCheckbox(wxCommandEvent & event)
{
	m_Changed = true;
	m_Save->Enable();
	m_Save->SetLabel(wxT("Save Changes"));

	if (event.IsChecked())
	{
		m_Setting_OutlineColor = true;
		m_PickOutlineColorButton->Enable();
	}

	else
	{
		m_Setting_OutlineColor = false;
		m_PickOutlineColorButton->Disable();
	}
}

void Settings::OnUseShapeColorCheckbox(wxCommandEvent & event)
{
	m_Changed = true;
	m_Save->Enable();
	m_Save->SetLabel(wxT("Save Changes"));

	if (event.IsChecked())
	{
		m_Setting_ShapeColor = true;
		m_PickShapeColorButton->Enable();
	}

	else
	{
		m_Setting_ShapeColor = false;
		m_PickShapeColorButton->Disable();
	}
}

void Settings::OnUseBackgroundColorCheckbox(wxCommandEvent & event)
{
	m_Changed = true;
	m_Save->Enable();
	m_Save->SetLabel(wxT("Save Changes"));

	if (event.IsChecked())
	{
		m_Setting_BackgroundColor = true;
		m_PickBackgroundColorButton->Enable();
	}

	else
	{
		m_Setting_BackgroundColor = false;
		m_PickBackgroundColorButton->Disable();
	}
}

void Settings::OnPickOutlineColorButton(wxCommandEvent & event)
{
	m_Save->Enable();
	m_Save->SetLabel(wxT("Save Changes"));

	ColorWindow * Window = new ColorWindow(this, wxT("Set RGB Value (Outline Color)"), wxSize(320, 350), m_config, SHAPE_OUTLINE_COLOR);
	Window->Show(true);
}

void Settings::OnPickShapeColorButton(wxCommandEvent & event)
{
	ColorWindow * Window = new ColorWindow(this, wxT("Set RGB Value (Shape Color)"), wxSize(320, 350), m_config, SHAPE_COLOR);
	Window->Show(true);
}

void Settings::OnPickBackgroundColorButton(wxCommandEvent & event)
{
	ColorWindow * Window = new ColorWindow(this, wxT("Set RGB Value (Background Color)"), wxSize(320, 350), m_config, BACKGROUND_COLOR);
	Window->Show(true);
}

void Settings::OnLoadGeneralSettings(wxCommandEvent & event)
{
	LoadGeneralSettingsLayout();
	m_Toolbar->EnableTool(ID_TOOLBAR_GENERAL_SETTINGS, false);
	m_Toolbar->EnableTool(ID_TOOLBAR_COLOR_SETTINGS, true);
}

void Settings::OnLoadColorSettings(wxCommandEvent & event)
{
	LoadColorSettingsLayout();
	m_Toolbar->EnableTool(ID_TOOLBAR_GENERAL_SETTINGS, true);
	m_Toolbar->EnableTool(ID_TOOLBAR_COLOR_SETTINGS, false);
}

void Settings::CreateSettings()
{
	m_config->Write(m_ClipboardKey, true);
	m_config->Write(m_SaveImagesKey, false);
	m_config->Write(m_DirectoryPathKey, m_ImageFilePath);
	m_config->Write(m_PlaySoundKey, false);
	m_config->Write(m_SoundFileKey, m_SoundFilePath);
	m_config->Write(m_UsingCustomOutlineColorKey, false);
	m_config->Write(m_UsingCustomShapeColorKey, false);
	m_config->Write(m_UsingCustomBackgroundColorKey, false);
	m_config->Write(m_RedKey_Outline, 255);
	m_config->Write(m_GreenKey_Outline, 255);
	m_config->Write(m_BlueKey_Outline, 255);
	m_config->Write(m_RedKey_Shape, 255);
	m_config->Write(m_GreenKey_Shape, 255);
	m_config->Write(m_BlueKey_Shape, 255);
	m_config->Write(m_RedKey_Background, 255);
	m_config->Write(m_GreenKey_Background, 255);
	m_config->Write(m_BlueKey_Background, 255);
}

void Settings::LoadSettings()
{
	m_config->Read(m_ClipboardKey, &m_Setting_CopyToClipboard);
	m_config->Read(m_SaveImagesKey, &m_Setting_SaveImages);
	m_config->Read(m_DirectoryPathKey, &m_ImageFilePath);
	m_config->Read(m_PlaySoundKey, &m_Setting_PlaySound);
	m_config->Read(m_SoundFileKey, &m_SoundFilePath);
	m_config->Read(m_UsingCustomOutlineColorKey, &m_Setting_OutlineColor);
	m_config->Read(m_UsingCustomShapeColorKey, &m_Setting_ShapeColor);
	m_config->Read(m_UsingCustomBackgroundColorKey, &m_Setting_BackgroundColor);
}

void Settings::SaveSettings()
{
	m_config->Write(m_ClipboardKey, m_Setting_CopyToClipboard);
	m_config->Write(m_SaveImagesKey, m_Setting_SaveImages);
	m_config->Write(m_DirectoryPathKey, m_ImageFilePath);
	m_config->Write(m_PlaySoundKey, m_Setting_PlaySound);
	m_config->Write(m_SoundFileKey, m_SoundFilePath);
	m_config->Write(m_UsingCustomOutlineColorKey, m_Setting_OutlineColor);
	m_config->Write(m_UsingCustomShapeColorKey, m_Setting_ShapeColor);
	m_config->Write(m_UsingCustomBackgroundColorKey, m_Setting_BackgroundColor);
}

void Settings::UpdateGUISettings() // Incoming spaghetti code.
{
	if (m_Setting_CopyToClipboard)
	{
		m_Clipboard->SetValue(true);
	}

	if (m_Setting_SaveImages)
	{
		m_SaveFile->SetValue(true);
	}

	else
	{
		m_SaveFileLocation->Disable();
	}

	if (m_Setting_PlaySound)
	{
		m_PlaySound->SetValue(true);
		m_PlaySoundPath->Enable();

		if (!m_SoundFilePath.empty())
		{
			m_PlaySoundButton->Enable();
		}
	}

	else
	{
		m_PlaySoundButton->Disable();
		m_PlaySoundPath->Disable();
	}

	if (m_Setting_OutlineColor)
	{
		m_ColorOutlineCheckBox->SetValue(true);
	}

	else
	{
		m_PickOutlineColorButton->Disable();
	}

	if (m_Setting_ShapeColor)
	{
		m_ColorShapeCheckBox->SetValue(true);
	}

	else
	{
		m_PickShapeColorButton->Disable();
	}

	if (m_Setting_BackgroundColor)
	{
		m_ColorBackgroundCheckBox->SetValue(true);
	}

	else
	{
		m_PickBackgroundColorButton->Disable();
	}
}

// End spaghetti code

void Settings::SetupToolbars()
{
	wxImage::AddHandler(new wxPNGHandler);
	m_Toolbar = CreateToolBar();
	m_General_Toolbutton = m_Toolbar->AddCheckTool(ID_TOOLBAR_GENERAL_SETTINGS, wxT("General Settings"), wxBitmap(wxT("Gear.png"), wxBITMAP_TYPE_PNG), wxNullBitmap, wxT("Show General Settings"));
	m_Color_Toolbutton = m_Toolbar->AddCheckTool(ID_TOOLBAR_COLOR_SETTINGS, wxT("Color Settings"), wxBitmap(wxT("RGB.png"), wxBITMAP_TYPE_PNG), wxNullBitmap, wxT("Show Color Settings"));
	m_Toolbar->EnableTool(ID_TOOLBAR_GENERAL_SETTINGS, false);
	m_Toolbar->Realize();
}

void Settings::LoadGeneralSettingsLayout()
{
	m_Clipboard->Show();
	m_SaveFile->Show();
	m_SaveFileLocation->Show();
	m_PlaySound->Show();
	m_PlaySoundButton->Show();
	m_PlaySoundPath->Show();

	m_ColorOutlineCheckBox->Hide();
	m_PickOutlineColorButton->Hide();
	m_ColorShapeCheckBox->Hide();
	m_PickShapeColorButton->Hide();
	m_ColorBackgroundCheckBox->Hide();
	m_PickBackgroundColorButton->Hide();
}

void Settings::LoadColorSettingsLayout()
{
	m_Clipboard->Hide();
	m_SaveFile->Hide();
	m_SaveFileLocation->Hide();
	m_PlaySound->Hide();
	m_PlaySoundButton->Hide();
	m_PlaySoundPath->Hide();

	m_ColorOutlineCheckBox->Show();
	m_PickOutlineColorButton->Show();
	m_ColorShapeCheckBox->Show();
	m_PickShapeColorButton->Show();
	m_ColorBackgroundCheckBox->Show();
	m_PickBackgroundColorButton->Show();

}

void Settings::AllocateControls()
{
	AllocateButtons();
	AllocateCheckBoxes();
}

void Settings::AllocateButtons()
{
	m_Save = new wxButton(m_Panel, ID_BUTTON_SAVE, wxT("No Changes Made"), wxPoint(75, 215), wxSize(120, 50));
	m_SaveFileLocation = new wxButton(m_Panel, ID_BUTTON_SET_FILE_LOCATION, wxT("Set File Path"), wxPoint(10, 70), wxSize(100, 25));
	m_PlaySoundPath = new wxButton(m_Panel, ID_BUTTON_SET_SOUND_PATH, wxT("Set Sound"), wxPoint(10, 130), wxSize(100, 25));
	m_PlaySoundButton = new wxButton(m_Panel, ID_BUTTON_PLAY_SOUND, wxT("Test Sound"), wxPoint(10, 155), wxSize(100, 25));
	m_PickOutlineColorButton = new wxButton(m_Panel, ID_BUTTON_PICK_OUTLINE_COLOR, wxT("Pick Custom Outline Color"), wxPoint(10, 50), wxSize(150, 25));
	m_PickShapeColorButton = new wxButton(m_Panel, ID_BUTTON_PICK_SHAPE_COLOR, wxT("Pick Custom Shape Color"), wxPoint(10, 100), wxSize(150, 25));
	m_PickBackgroundColorButton = new wxButton(m_Panel, ID_BUTTON_PICK_BACKGROUND_COLOR, wxT("Pick Custom Background Color"), wxPoint(10, 150), wxSize(200, 25));
}

void Settings::AllocateCheckBoxes()
{
	m_Clipboard = new wxCheckBox(m_Panel, ID_CHECKBOX_CLIPBOARD, wxT("Always copy image to Clipboard"), wxPoint(10, 20), wxSize(200, 20));
	m_SaveFile = new wxCheckBox(m_Panel, ID_CHECKBOX_SAVE_FILE, wxT("Save images"), wxPoint(10, 40), wxSize(100, 20));
	m_PlaySound = new wxCheckBox(m_Panel, ID_CHECKBOX_PLAY_SOUND, wxT("Play sound after capturing image"), wxPoint(10, 100), wxSize(195, 25));
	m_ColorOutlineCheckBox = new wxCheckBox(m_Panel, ID_CHECKBOX_USE_OUTLINE_COLOR, wxT("Use Custom Outline Color"), wxPoint(10, 20), wxSize(170, 25));
	m_ColorShapeCheckBox = new wxCheckBox(m_Panel, ID_CHECKBOX_USE_SHAPE_COLOR, wxT("Use Custom Shape Color"), wxPoint(10, 80), wxSize(200, 20));
	m_ColorBackgroundCheckBox = new wxCheckBox(m_Panel, ID_CHECKBOX_USE_BACKGROUND_COLOR, wxT("Use Custom Background Color"), wxPoint(10, 130), wxSize(200, 20));
}

// This makes sure manual changes to the config file don't go over 255 because undefined behavior could result
/*void Settings::CheckColors()
{
	if (m_Red > 255)
	{
		m_Red = 255;
	}

	if (m_Green > 255)
	{
		m_Green = 255;
	}

	if (m_Blue > 255)
	{
		m_Blue = 255;
	}
}
*/