//
// Created by blinku on 20.03.19.
//

#pragma once

#include <wx/wxprec.h>
#include <wx/wx.h>
#include "frame.hpp"

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
    MyFrame* m_Frame;
};
