//
// Created by blinku on 20.03.19.
//

#include "frame.hpp"
#include "wx/dcbuffer.h"
#include "wx/dcgraph.h"
#include <wx/colordlg.h>

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    m_ButtonSaveFile = new wxButton(this, ID_SAVEBUTTON, wxT("Zapis do pliku"));

    m_Checkbox = new wxCheckBox(this, ID_CHECKBOX, wxT("banan"));

    m_Scrollbar = new wxScrollBar(this, ID_SCROLLBAR, wxDefaultPosition, wxSize(200, 20));
    m_Scrollbar->SetScrollbar(0, 1, 100, 1);
    m_Scrollbar->Disable();

    m_ButtonColorWheel = new wxButton(this, ID_COLORWHEELBUTTON, wxT("kolor gwiazdki"));

    m_ProgressBar = new wxGauge(this, wxID_ANY, 99, wxDefaultPosition, wxSize(200, 20));

    m_TextBox = new wxTextCtrl(this, wxID_ANY, wxT("tekst"));

    m_ComboBox = new wxComboBox(this, wxID_ANY, wxT("gwiazdka"));
    m_ComboBox->Append(wxT("gwiazdka"));
    m_ComboBox->Append(wxT("ksiezyc"));
    m_ComboBox->Append(wxT("slonce"));

    m_Canvas = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    m_Canvas->SetBackgroundColour(wxColour(*wxWHITE));

    topSizer = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(topSizer);
    this->SetAutoLayout(true);
    topSizer->Add(m_Canvas, 1, wxALIGN_CENTER | wxEXPAND, 5);

    menuSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(menuSizer, 1, wxALIGN_CENTER | wxEXPAND);

    menuSizer->Add(m_ButtonSaveFile, 0, wxALIGN_CENTER | wxALL , 5);
    menuSizer->Add(m_Checkbox,0, wxALIGN_CENTER | wxALL, 5);
    menuSizer->Add(m_Scrollbar, 0, wxALIGN_CENTER | wxALL, 5);
    menuSizer->Add(m_ButtonColorWheel, 0, wxALIGN_CENTER | wxALL, 5);
    menuSizer->Add(m_ProgressBar, 0, wxALIGN_CENTER | wxALL , 5);
    menuSizer->Add(m_TextBox,0, wxALIGN_CENTER | wxALL, 5);
    menuSizer->Add(m_ComboBox, 0, wxALIGN_CENTER | wxALL, 5);

    Layout();
    GetSizer()->SetSizeHints(this);
    Center();

    wxImage bananaImage = wxImage();
    wxImage::AddHandler(new wxPNGHandler);
    bananaImage.LoadFile("assets/banan.png", wxBITMAP_TYPE_PNG);
    m_Banana = wxBitmap{bananaImage};

    Bind(wxEVT_BUTTON, [&](wxCommandEvent& e)
    {
        wxFileDialog choseFile(nullptr, "Save", "", "", "PNG files (*.png)|*.png", wxFD_SAVE);
        if(choseFile.ShowModal() == wxID_CANCEL) return;
        wxImage image = m_WholeCanvas.ConvertToImage();
        wxImage::AddHandler(new wxPNGHandler);
        image.SaveFile(choseFile.GetPath());
    }, ID_SAVEBUTTON);

    Bind(wxEVT_SCROLL_THUMBTRACK, [&](wxCommandEvent& e)
    {
        m_ProgressBar->SetValue(m_Scrollbar->GetThumbPosition());
        m_BananaOffset = m_Scrollbar->GetThumbPosition();
    });

    Bind(wxEVT_CHECKBOX, [&](wxCommandEvent& e)
    {
        m_Scrollbar->Enable(m_Checkbox->IsChecked());
    });

    Bind(wxEVT_BUTTON, [&](wxCommandEvent& e)
    {
        wxColourDialog dialog(this, nullptr);
        if(dialog.ShowModal() == wxID_CANCEL) return;
        m_StarColour = dialog.GetColourData().GetColour();
        Draw();
    }, ID_COLORWHEELBUTTON);

    Bind(wxEVT_TEXT, [&](wxCommandEvent& e)
    {
        m_TextFromBox = m_TextBox->GetValue();
        Draw();
    });

    Bind(wxEVT_COMBOBOX, [&](wxCommandEvent& e)
    {
        if("gwiazdka" == m_ComboBox->GetValue())
        {
            m_CurrShape = ShapeToDraw::STAR;
        } else if("ksiezyc" == m_ComboBox->GetValue())
        {
            m_CurrShape = ShapeToDraw::MOON;
        } else
        {
            m_CurrShape = ShapeToDraw::SUN;
        }

        Draw();
    });

    Bind(wxEVT_UPDATE_UI, [&](wxCommandEvent& e)
    {
        Draw();
    });
}

void MyFrame::Draw()
{
    wxClientDC canvasHandler(m_Canvas);
    wxBufferedDC drawBuffer(&canvasHandler, m_WholeCanvas);
    wxGCDC gcdc(drawBuffer);
    m_WholeCanvas = wxBitmap(m_Canvas->GetSize().x, m_Canvas->GetSize().y);

    gcdc.SetBackground(*wxWHITE_BRUSH);
    gcdc.Clear();

    int sizeX = m_Canvas->GetSize().x;
    int sizeY = m_Canvas->GetSize().y;

    if(sizeX > 193.5 && sizeY > 181) {
        gcdc.SetDeviceOrigin(sizeX/2 - 193.5, sizeY/2 - 181);
    }

    if(m_Checkbox->IsChecked())
        gcdc.DrawBitmap(m_Banana, 120, 180 - m_BananaOffset / 2);

    gcdc.DrawCircle(wxPoint(188, 143), 20);

    if(m_Checkbox->IsChecked())
    {
        gcdc.DrawEllipse(wxPoint(176, 135), wxSize(10, 7));
        gcdc.DrawEllipse(wxPoint(191, 135), wxSize(10, 7));
        gcdc.DrawEllipticArc(wxPoint(174, 148), wxSize(26, 5), 180, 360);
    } else
    {
        gcdc.DrawEllipse(wxPoint(176, 135), wxSize(10, 7));
        gcdc.DrawEllipse(wxPoint(191, 133), wxSize(7, 10));
        gcdc.DrawEllipticArc(174, 148, 26, 5, 0, 180);
    }

    gcdc.DrawLine(188, 164, 188, 234);
    gcdc.DrawLine(188, 234, 159, 262);
    gcdc.DrawLine(188, 234, 217, 262);
    gcdc.DrawLine(188, 173, 227, 192);
    gcdc.DrawLine(188, 173, 149, 192 - m_BananaOffset / 2);

    wxString text1(m_TextFromBox);
    wxString text2(m_TextFromBox);
    gcdc.SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Calibri"));
    gcdc.DrawText(text1, 98, 253);
    gcdc.SetFont(wxFont(40, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false, "Calibri"));
    gcdc.DrawRotatedText(text2, 239, 253, 90);

    if(m_CurrShape == ShapeToDraw::STAR)
    {
        gcdc.SetBrush(wxBrush(m_StarColour));
        gcdc.SetPen(wxPen(m_StarColour));
        wxPoint points[5] = {
            wxPoint(68, 23),
            wxPoint(93, 68),
            wxPoint(38, 43),
            wxPoint(98, 43),
            wxPoint(44, 68)
        };

        gcdc.DrawPolygon(5, points, 50, 50);
    } else if(m_CurrShape == ShapeToDraw::MOON)
    {
        gcdc.SetBrush(wxBrush(wxColour(*wxLIGHT_GREY)));
        gcdc.SetPen(wxPen(wxColour(*wxLIGHT_GREY)));
        gcdc.DrawCircle(100, 100, 30);

        gcdc.SetBrush(wxBrush(wxColour(*wxWHITE)));
        gcdc.SetPen(wxPen(wxColour(*wxWHITE)));
        gcdc.DrawCircle(80, 80, 30);

        gcdc.SetBrush(wxBrush(wxColour(*wxBLACK)));
        gcdc.SetPen(wxPen(wxColour(*wxBLACK)));
        gcdc.DrawCircle(110, 95, 5);

        gcdc.DrawLine(100, 105, 110, 110);
    } else
    {
        gcdc.SetBrush(wxBrush(wxColour(*wxYELLOW)));
        gcdc.SetPen(wxPen(wxColour(*wxYELLOW)));
        gcdc.DrawCircle(100, 100, 30);
    }
}
