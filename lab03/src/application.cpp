//
// Created by blinku on 20.03.19.
//

#include "application.hpp"
#include "frame.hpp"

bool MyApp::OnInit()
{
    m_Frame = new MyFrame("Lab03", wxPoint(0, 0), wxSize(800, 600));
    m_Frame->Show(true);
    return true;
}