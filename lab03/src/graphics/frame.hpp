//
// Created by blinku on 20.03.19.
//

#pragma once

#include <wx/wx.h>

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    void Draw();

private:
    enum MenuID
    {
        ID_SAVEBUTTON,
        ID_COLORWHEELBUTTON,
        ID_CHECKBOX,
        ID_SCROLLBAR
    };

    enum class ShapeToDraw
    {
        STAR,
        MOON,
        SUN
    };

private:
    wxPanel* m_Menu;
    wxPanel* m_Canvas;
    wxBoxSizer* topSizer;
    wxBoxSizer* menuSizer;

    wxButton* m_ButtonSaveFile;
    wxButton* m_ButtonColorWheel;
    wxCheckBox* m_Checkbox;
    wxScrollBar* m_Scrollbar;
    wxGauge* m_ProgressBar;
    wxTextCtrl* m_TextBox;
    wxComboBox* m_ComboBox;

    wxString m_TextFromBox = "tekst";

    wxBitmap m_WholeCanvas;
    wxBitmap m_Banana;

    ShapeToDraw m_CurrShape;

    wxColour m_StarColour = wxColour(*wxBLACK);

    int m_BananaOffset = 0;

};

