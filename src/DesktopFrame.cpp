#include "DesktopFrame.h"

BEGIN_EVENT_TABLE(DesktopFrame, wxFrame)
EVT_LEFT_DOWN(DesktopFrame::OnMouseDown)
EVT_LEFT_UP(DesktopFrame::OnMouseUp)
EVT_MOTION(DesktopFrame::OnMouseMove)
EVT_KEY_DOWN(DesktopFrame::OnESCKeyPressed)
EVT_CLOSE(DesktopFrame::OnClose)
END_EVENT_TABLE()


DesktopFrame::DesktopFrame(wxWindow * Window, const wxSize & Size, int WindowID) : wxFrame(Window, WindowID, wxEmptyString, wxDefaultPosition, Size, wxSTAY_ON_TOP), m_Size(Size), m_Window(Window)
{
	m_ColorsLoaded = false;
	LoadSettings();
	Window->Hide();
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

		wxSize ScreenRes = screendc.GetSize();
		wxBitmap ScreenBitmap(ScreenRes.GetWidth(), ScreenRes.GetHeight());
		memdc.SelectObject(ScreenBitmap);
		memdc.Blit(0, 0, ScreenRes.GetWidth(), ScreenRes.GetHeight(), &screendc, 0, 0);
		memdc.SelectObject(wxNullBitmap);
		wxBitmap Snippet = ScreenBitmap.GetSubBitmap(CroppedRegion);

		if (wxTheClipboard->Open())
		{
			wxTheClipboard->Clear();
			wxTheClipboard->SetData(new wxBitmapDataObject(Snippet));
			wxTheClipboard->Close();
		}
	}

	if (m_Setting_SaveImages)
	{
		wxImage::AddHandler(new wxJPEGHandler);
		wxMemoryDC memdc(&dc);

		wxSize ScreenRes = screendc.GetSize();

		//wxScreenDC screendc;
		//wxBitmap snippet(CroppedRegion.GetWidth(), CroppedRegion.GetHeight());
		wxBitmap ScreenBitmap(ScreenRes.GetWidth(), ScreenRes.GetHeight());
		memdc.SelectObject(ScreenBitmap);
		memdc.Blit(0, 0, ScreenRes.GetX(), ScreenRes.GetY(), &screendc, 0, 0); // works but slow
		memdc.SelectObject(wxNullBitmap);
		//memdc.Blit(m_End, CroppedRegion.GetSize(), &screendc, m_Start);
		//memdc.DrawBitmap(snippet, ScreenRes.x, ScreenRes.y);

		wxBitmap CroppedImage = ScreenBitmap.GetSubBitmap(CroppedRegion);
		CroppedImage.SaveFile(wxT("test.jpg"), wxBITMAP_TYPE_JPEG);
	}
	
	this->Destroy();
	m_Window->Show();
}

void DesktopFrame::OnMouseMove(wxMouseEvent & event)
{
	if (m_IsMousePressed)
	{
		// TO DO. Improve this.
		wxWindowDC windc(this);
		//wxGraphicsContext * gc = wxGraphicsContext::Create(windc);
		wxBufferedDC dc(&windc);

		LoadColors(dc);
		//LoadColors(gc);

		wxPoint MousePos = event.GetLogicalPosition(dc);

		wxRect RectToDraw(MousePos, m_Start);

		dc.Clear();
		dc.DrawRectangle(RectToDraw);

		/*if (m_Start.x > MousePos.x)
		{
			gc->DrawRectangle(RectToDraw.x, RectToDraw.y, m_Start.x - MousePos.x, m_Start.y - MousePos.y);
		}

		else if (m_Start.x < MousePos.x)
		{
			gc->DrawRectangle(RectToDraw.x, RectToDraw.y, m_Start.x + MousePos.x, m_Start.y - MousePos.y);
		}
		*/

		//delete gc;
	}
}

void DesktopFrame::OnClose(wxCloseEvent & event) // incase if the user closes the window by hitting alt tab then close
{
	this->Destroy();
	m_Window->Show();
}

void DesktopFrame::LoadColors(wxBufferedDC & dc)
{
	if (m_Setting_OutlineColor)
	{
		dc.SetPen(wxPen(wxColour(m_Red_Outline, m_Green_Outline, m_Blue_Outline)));
	}

	else
	{
		dc.SetPen(wxPen(*wxGREY_PEN));
	}

	if (m_Setting_ShapeColor)
	{
		dc.SetBrush(wxBrush(wxColour(m_Red_Shape, m_Green_Shape, m_Blue_Shape, m_Transparency)));//, wxBRUSHSTYLE_TRANSPARENT);
	}

	else
	{
		dc.SetBrush(wxBrush(*wxWHITE_BRUSH));
	}

	m_ColorsLoaded = true;
}

// For testing purposes. Delete this at some point
void DesktopFrame::LoadColors(wxGraphicsContext * gc)
{
	if (m_Setting_OutlineColor)
	{
		gc->SetPen(wxPen(wxColour(m_Red_Outline, m_Green_Outline, m_Blue_Outline)));
	}

	else
	{
		gc->SetPen(wxPen(*wxBLACK_PEN));
	}

	if (m_Setting_ShapeColor)
	{
		gc->SetBrush(wxBrush(wxColour(m_Red_Shape, m_Green_Shape, m_Blue_Shape, m_Transparency)));
	}

	else
	{
		gc->SetBrush(wxBrush(wxColour(255, 255, 255, 100))); // White brush.
	}
}

void DesktopFrame::OnESCKeyPressed(wxKeyEvent & event)
{
	if (event.GetKeyCode() == wxKeyCode::WXK_ESCAPE)
	{
		this->Destroy();
		m_Window->Show();
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

		const wxString TransparencyKey = wxT("Shape Transparency:");


		wxFileConfig config(wxEmptyString, wxEmptyString, wxT("Settings.ini"), wxT("Settings.ini"), wxCONFIG_USE_RELATIVE_PATH);
		config.Read(m_ClipboardKey, &m_Setting_CopyToClipboard);
		config.Read(m_SaveImagesKey, &m_Setting_SaveImages);
		config.Read(m_DirectoryPathKey, &m_DirectoryFilePath);
		config.Read(m_PlaySoundKey, &m_Setting_PlaySound);
		config.Read(m_SoundFileKey, &m_SoundPath);
		config.Read(TransparencyKey, &m_Transparency);
		//config.Read(m_MinimizeNotifyKey, &m_setting_m)
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
	}
}
