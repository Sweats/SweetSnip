#pragma once

#include "Includes.h"
#include "ColorWindow.h"
#include "TransparencyWindow.h"

#ifndef SETTINGS_H
#define SETTINGS_H


class Settings: public wxFrame
{
public:
	Settings(wxWindow * window, const wxString & Title, const wxPoint & Point, const wxSize & Size);
	~Settings();

private:
	// General Controls
	wxPanel * m_Panel;
	wxButton * m_Save; // for save button
	wxCheckBox * m_Clipboard; // Always Copy Image To Clipboard
	wxCheckBox * m_SaveFile; // Save Screenshots
	wxButton * m_SaveFileLocation; // Set file path.
	wxCheckBox * m_PlaySound; // Enable/Disable sounds
	wxButton * m_PlaySoundPath; // Set filepath for sound
	wxButton * m_PlaySoundButton; // Test Sound
	wxCheckBox * m_MinimizeNotify; // Notify on Minimize


	// Color controls
	wxCheckBox * m_ColorOutlineCheckBox; // "Use custom shape outline color"
	wxCheckBox * m_ColorShapeCheckBox; // "Use custom shape color"
	wxCheckBox * m_ColorBackgroundCheckBox; // "Use custom background color"


	wxButton * m_PickOutlineColorButton; // "Pick Outline Color" Button
	wxButton * m_PickShapeColorButton; // "Pick Shape Color" Button
	wxButton * m_PickBackgroundColorButton; // "Pick Background Color" Button.

	wxButton * m_PickTransparencyButton;

	// Misc 

	wxWindow * m_Window;
	wxFileConfig * m_config;
	wxToolBar * m_Toolbar;
	wxToolBarToolBase * m_Color_Toolbutton;
	wxToolBarToolBase * m_General_Toolbutton;
	wxTextCtrl * m_DirPathWarning;
	wxTextCtrl * m_SoundPathWarning;

	//wxSound * m_Sound;
	bool m_Changed;
	bool m_DirPathChanged;

	void OnSaveSettings(wxCommandEvent & event);
	void OnClipboardChanged(wxCommandEvent & event);
	void OnSaveFileCheckboxChanged(wxCommandEvent & event);
	void OnSetFilePath(wxCommandEvent & event); // for setting file path where images are saved.
	void OnPlaySoundCheckboxChanged(wxCommandEvent & event);
	void OnPlaySoundFilePath(wxCommandEvent & event);
	void OnPlaySoundButton(wxCommandEvent & event);
	void OnClose(wxCloseEvent & event);
	void OnUseOutlineColorCheckbox(wxCommandEvent & event);
	void OnUseShapeColorCheckbox(wxCommandEvent & event);
	void OnUseBackgroundColorCheckbox(wxCommandEvent & event);
	void OnPickOutlineColorButton(wxCommandEvent & event);
	void OnPickShapeColorButton(wxCommandEvent & event);
	void OnPickBackgroundColorButton(wxCommandEvent & event);
	void OnLoadGeneralSettings(wxCommandEvent & event);
	void OnLoadColorSettings(wxCommandEvent & event);
	void OnMinimizeNotifyCheckbox(wxCommandEvent & event);
	void OnPickTransparencyButton(wxCommandEvent & event);
	void CreateSettings();
	void LoadSettings();
	void UpdateGUISettings();
	void SaveSettings();
	void SetupToolbars();
	void LoadGeneralSettingsLayout();
	void LoadColorSettingsLayout();
	void AllocateControls();
	void AllocateTextControls();

	void AllocateCheckBoxes();
	void AllocateButtons();
	void UpdateTxtCtrlGreen();
	void UpdateTxtCtrlOrange();
	void UpdateTxtCtrlRed();

	//void CheckColors();
	

	// SETTINGS
	const wxString m_ClipboardKey = wxT("Always copy image to clipboard");
	const wxString m_SaveImagesKey = wxT("Save images");
	const wxString m_DirectoryPathKey = wxT("Directory path to store saved images");
	const wxString m_PlaySoundKey = wxT("Play Sounds");
	const wxString m_SoundFileKey = wxT("Sound File");
	const wxString m_MinimizeNotifyKey = wxT("Notify user when program is minimized");

	wxString m_ImageFilePath;
	wxString m_SoundFilePath;

	// COLORS
	
	const wxString m_UsingCustomOutlineColorKey = wxT("Custom Color");
	const wxString m_RedKey_Outline = wxT("Shape Outline Color: Red");
	const wxString m_GreenKey_Outline = wxT("Shape Outline Color: Green");
	const wxString m_BlueKey_Outline = wxT("Shape Outline Color: Blue");

	const wxString m_UsingCustomShapeColorKey = wxT("Custom Shape Color");
	const wxString m_RedKey_Shape = wxT("Shape Color: Red");
	const wxString m_GreenKey_Shape = wxT("Shape Color: Green");
	const wxString m_BlueKey_Shape = wxT("Shape Color: Blue");


	const wxString m_UsingCustomBackgroundColorKey = wxT("Custom Background Color");
	const wxString m_RedKey_Background = wxT("Background Color: Red");
	const wxString m_GreenKey_Background = wxT("Background Color: Green");
	const wxString m_BlueKey_Background = wxT("Background Color: Blue");

	const wxString m_TransparencyKey = wxT("Shape Transparency:");

	bool m_Setting_CopyToClipboard;
	bool m_Setting_SaveImages;
	bool m_Setting_PlaySound;
	bool m_Setting_Notify_Minimize;


	bool m_Setting_OutlineColor;
	bool m_Setting_ShapeColor;
	bool m_Setting_BackgroundColor;

	DECLARE_EVENT_TABLE()
};

enum
{
	ID_CLOSE,
	ID_CHECKBOX_CLIPBOARD,
	ID_CHECKBOX_SAVE_FILE,
	ID_BUTTON_SAVE,
	ID_BUTTON_SET_FILE_LOCATION,
	ID_CHECKBOX_PLAY_SOUND,
	ID_BUTTON_SET_SOUND_PATH,
	ID_BUTTON_PLAY_SOUND,
	ID_CHECKBOX_USE_OUTLINE_COLOR,
	ID_CHECKBOX_USE_SHAPE_COLOR,
	ID_CHECKBOX_USE_BACKGROUND_COLOR,
	ID_BUTTON_PICK_OUTLINE_COLOR,
	ID_BUTTON_PICK_SHAPE_COLOR,
	ID_BUTTON_PICK_BACKGROUND_COLOR,
	ID_TOOLBAR_GENERAL_SETTINGS,
	ID_TOOLBAR_COLOR_SETTINGS,
	ID_CHECKBOX_MINIMIZE_NOTIFY,
	ID_BUTTON_PICK_TRANSPARENCY,
};

#endif // SETTINGS_H

