#include "DesktopFrame.h"

BEGIN_EVENT_TABLE(DesktopFrame, wxFrame)
EVT_LEFT_DOWN(DesktopFrame::OnMouseDown)
EVT_LEFT_UP(DesktopFrame::OnMouseUp)
EVT_MOTION(DesktopFrame::OnMouseMove)
EVT_KEY_DOWN(DesktopFrame::OnESCKeyPressed)
EVT_CLOSE(DesktopFrame::OnClose)
END_EVENT_TABLE()


DesktopFrame::DesktopFrame(wxWindow * Window, const wxSize & Size, int WindowID, bool IsMinimized) : wxFrame(Window, WindowID, wxEmptyString, wxDefaultPosition, Size, wxSTAY_ON_TOP | wxBORDER_NONE), m_Size(Size), m_Window(Window)
{
	if (Window != NULL)
	{
		Window->Hide();
	}

	m_Minimized = IsMinimized;

	m_ColorsLoaded = false;
	LoadSettings();
	this->SetBackgroundColour(wxColour(m_Red_Background, m_Green_Background, m_Blue_Background));
	this->SetTransparent(m_Transparency);
	this->SetFocus(); // doesn't always work if we're entering this window from hotkey
	this->SetCursor(wxCursor(wxStockCursor::wxCURSOR_CROSS));

	m_IsMousePressed = false;
}


DesktopFrame::~DesktopFrame()
{
}

void DesktopFrame::OnMouseDown(wxMouseEvent & event)
{
	m_Start = event.GetPosition();
	m_IsMousePressed = true;
}

void DesktopFrame::OnMouseUp(wxMouseEvent & event)
{
	// TO DO: Don't blit the entire screen then get portion. blit only what we need.
	m_IsMousePressed = false;
	
	wxWindowDC dc(this);
	wxScreenDC screendc;
	wxMemoryDC memdc(&dc);

	this->Hide();
	m_End = event.GetPosition();
	wxRect CroppedRegion(m_End, m_Start);
	wxBitmap ScreenBitmap(m_Size.GetWidth(), m_Size.GetHeight());
	memdc.SelectObject(ScreenBitmap);
	memdc.Blit(0, 0, m_Size.GetWidth(), m_Size.GetHeight(), &screendc, 0, 0);
	memdc.SelectObject(wxNullBitmap);
	wxBitmap Snippet = ScreenBitmap.GetSubBitmap(CroppedRegion);

	if (m_Setting_PlaySound)
	{
		wxSound sound(m_SoundPath, false);

		if (sound.IsOk())
		{
			sound.Play(wxSOUND_ASYNC);
		}
	}

	if (m_Setting_CopyToClipboard)
	{
		#ifdef __linux__ 
		wxTheClipboard->UsePrimarySelection(true);
		#endif

		if (wxTheClipboard->Open())
		{
			wxTheClipboard->Clear();
			wxTheClipboard->SetData(new wxBitmapDataObject(Snippet));
			wxTheClipboard->Close();
		}
	}

	if (m_Setting_SaveImages)
	{
		if (!m_DirectoryFilePath.empty())
		{
			wxImage::AddHandler(new wxJPEGHandler);
			wxMilliClock_t TimeStamp = wxGetLocalTime();
			wxString FileName = m_DirectoryFilePath + "\\IMG_" + wxString::Format(wxT("%lli"), TimeStamp) + ".jpg";
			Snippet.SaveFile(FileName, wxBITMAP_TYPE_JPEG);
		}
	}

	this->Destroy();

	if (!m_Minimized)
	{
		if (m_Window != NULL)
		{
			m_Window->Show();
		}
	}
}

void DesktopFrame::OnMouseMove(wxMouseEvent & event)
{
	if (m_IsMousePressed)
	{
		wxWindowDC windc(this);
		wxBufferedDC dc(&windc);
		wxGraphicsContext * gc = wxGraphicsContext::Create(dc);
		LoadColors(gc);
		wxPoint MousePos = event.GetLogicalPosition(dc);
		wxRect RectToDraw(MousePos, m_Start);
		dc.Clear();
		gc->DrawRectangle(RectToDraw.GetX(), RectToDraw.GetY(), RectToDraw.GetWidth(), RectToDraw.GetHeight());
		delete gc;
	}
}

void DesktopFrame::OnClose(wxCloseEvent & event) // incase if the user closes the window by hitting alt tab then close
{
	this->Destroy();

	if (!m_Minimized)
	{
		if (m_Window != NULL)
		{
			m_Window->Show();
		}
	}
}

void DesktopFrame::LoadColors(wxGraphicsContext * gc)
{
	gc->SetPen(wxPen(wxColour(m_Red_Outline, m_Green_Outline, m_Blue_Outline)));
	gc->SetBrush(wxBrush(wxColour(m_Red_Shape, m_Green_Shape, m_Blue_Shape, m_ShapeTransparency)));
}

void DesktopFrame::OnESCKeyPressed(wxKeyEvent & event)
{
	if (event.GetKeyCode() == wxKeyCode::WXK_ESCAPE)
	{
		this->Destroy();

		if (!m_Minimized)
		{
			if (m_Window != NULL)
			{
				m_Window->Show();
			}
		}
	}
}

void DesktopFrame::CheckValues() // Incase if user manually changes the ini file for some reason and doesn't go into settings.
{
	if (m_Red_Outline > 255)
	{
		m_Red_Outline = 255;
	}

	if (m_Green_Outline > 255)
	{
		m_Green_Outline = 255;
	}

	if (m_Blue_Outline > 255)
	{
		m_Blue_Outline = 255;
	}

	if (m_Red_Shape > 255)
	{
		m_Red_Shape = 255;
	}

	if (m_Green_Shape > 255)
	{
		m_Green_Shape = 255;
	}

	if (m_Blue_Shape > 255)
	{
		m_Blue_Shape = 255;
	}

	if (m_Red_Background > 255)
	{
		m_Red_Background = 255;
	}

	if (m_Green_Background > 255)
	{
		m_Green_Background = 255;
	}

	if (m_Blue_Background > 255)
	{
		m_Blue_Background = 255;
	}

	if (m_Transparency > 255)
	{
		m_Transparency = 255;
	}
}

void DesktopFrame::LoadSettings()
{
	if (!wxFileName::Exists(wxT("Settings.ini")))
	{
		m_Setting_CopyToClipboard = true;
		m_Setting_PlaySound = false;
		m_Setting_OutlineColor = false;
		m_Setting_ShapeColor = false;
		m_Setting_BackgroundColor = false;
		m_Red_Background = 128;
		m_Green_Background = 128;
		m_Blue_Background = 128;
		m_ShapeTransparency = 125;
		m_Transparency = 100;
		m_Red_Shape = 255;
		m_Green_Shape = 255;
		m_Blue_Shape = 255;
		m_Red_Outline = 255;
		m_Green_Outline = 0;
		m_Blue_Outline = 0;
	}

	else
	{
		const wxString m_ClipboardKey = wxT("Always copy image to clipboard");
		const wxString m_SaveImagesKey = wxT("Save images");
		const wxString m_DirectoryPathKey = wxT("Directory path to store saved images");
		const wxString m_PlaySoundKey = wxT("Play Sounds");
		const wxString m_SoundFileKey = wxT("Sound File");
		const wxString m_MinimizeNotifyKey = wxT("Notify user when program is minimized");

		const wxString m_UsingCustomBackgroundColorKey = wxT("Custom Background Color");
		const wxString m_UsingCustomShapeColorKey = wxT("Custom Shape Color");
		const wxString m_UsingCustomOutlineColorKey = wxT("Custom Color");

		const wxString m_RedKey_Background = wxT("Background Color: Red");
		const wxString m_GreenKey_Background = wxT("Background Color: Green");
		const wxString m_BlueKey_Background = wxT("Background Color: Blue");

		const wxString m_RedKey_Shape = wxT("Shape Color: Red");
		const wxString m_GreenKey_Shape = wxT("Shape Color: Green");
		const wxString m_BlueKey_Shape = wxT("Shape Color: Blue");

		const wxString m_RedKey_Outline = wxT("Shape Outline Color: Red");
		const wxString m_GreenKey_Outline = wxT("Shape Outline Color: Green");
		const wxString m_BlueKey_Outline = wxT("Shape Outline Color: Blue");

		const wxString TransparencyKey = wxT("Background Transparency");
		const wxString ShapeTransparencyKey = wxT("Shape Transparency");

		wxFileConfig config(wxEmptyString, wxEmptyString, wxT("Settings.ini"), wxT("Settings.ini"), wxCONFIG_USE_RELATIVE_PATH);
		config.Read(m_ClipboardKey, &m_Setting_CopyToClipboard);
		config.Read(m_SaveImagesKey, &m_Setting_SaveImages);
		config.Read(m_DirectoryPathKey, &m_DirectoryFilePath);
		config.Read(m_PlaySoundKey, &m_Setting_PlaySound);
		config.Read(m_SoundFileKey, &m_SoundPath);
		config.Read(TransparencyKey, &m_Transparency);
		config.Read(ShapeTransparencyKey, &m_ShapeTransparency);
		config.Read(m_RedKey_Outline, &m_Red_Outline);
		config.Read(m_GreenKey_Outline, &m_Green_Outline);
		config.Read(m_BlueKey_Outline, &m_Blue_Outline);
		config.Read(m_RedKey_Shape, &m_Red_Shape);
		config.Read(m_GreenKey_Shape, &m_Green_Shape);
		config.Read(m_BlueKey_Shape, &m_Blue_Shape);
		config.Read(m_RedKey_Background, &m_Red_Background);
		config.Read(m_GreenKey_Background, &m_Green_Background);
		config.Read(m_BlueKey_Background, &m_Blue_Background);
		config.Read(m_UsingCustomOutlineColorKey, &m_Setting_OutlineColor);
		config.Read(m_UsingCustomShapeColorKey, &m_Setting_ShapeColor);
		config.Read(m_UsingCustomBackgroundColorKey, &m_Setting_BackgroundColor);

		if (!m_Setting_BackgroundColor)
		{
			m_Red_Background = 128;
			m_Green_Background = 128;
			m_Blue_Background = 128;
		}

		if (!m_Setting_ShapeColor)
		{
			m_Red_Shape = 255;
			m_Green_Shape = 255;
			m_Blue_Shape = 255;
		}

		if (!m_Setting_OutlineColor)
		{
			m_Red_Outline = 255;
			m_Green_Outline = 0;
			m_Blue_Outline = 0;
		}

		CheckValues();
	}
}
