//
// Created by blinku on 15.03.19.
//

#include "application.hpp"
#include "graphics/window.hpp"

Application* Application::m_Instance = nullptr;
std::unique_ptr<Window> Application::m_Window = nullptr;
bool Application::m_Running = true;

Application::Application()
{
    m_Window = std::unique_ptr<Window>(Window::CreateWindow());
}

Application* Application::CreateApplication()
{
    if(!m_Instance)
        m_Instance = new Application();
    return m_Instance;
}

void Application::Run()
{
    while(m_Running)
    {
        m_Window->RunEvents();
        m_Window->Clear();
        m_Window->Render();
        m_Window->Display();
    }
}

void Application::CloseApplication()
{
    m_Window->CloseWindow();
    m_Running = false;
}
