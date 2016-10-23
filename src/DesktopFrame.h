#pragma once

#include "Includes.h"

#ifndef DESKTOPFRAME_H
#define DESKTOPFRAME_H


class DesktopFrame: public wxFrame
{
public:
	DesktopFrame(wxWindow * Window, const wxSize & Size);
	~DesktopFrame();

private:
	void OnMouseDown(wxMouseEvent & event);
	void OnMouseUp(wxMouseEvent & event);
	void OnMouseMove(wxMouseEvent & event);
	bool m_IsMousePressed;
	bool m_ColorsLoaded;
	void LoadColors(wxBufferedDC & dc);
	void LoadColors(wxGraphicsContext * gc);
	void LoadSettings();

	int m_Red_Outline;
	int m_Green_Outline;
	int m_Blue_Outline;

	int m_Red_Shape;
	int m_Green_Shape;
	int m_Blue_Shape;

	int m_Red_Background;
	int m_Green_Background;
	int m_Blue_Background;

	bool m_Setting_CopyToClipboard;
	bool m_Setting_SaveImages;
	bool m_Setting_PlaySound;

	bool m_Setting_OutlineColor;
	bool m_Setting_ShapeColor;
	bool m_Setting_BackgroundColor;

	wxString m_SoundPath;
	wxString m_DirectoryFilePath;


	bool m_IsDragging;
	wxPoint m_Start;
	wxPoint m_End;
	wxSize m_Size;

	DECLARE_EVENT_TABLE()

};

#endif // DESKTOPFRAME_H

