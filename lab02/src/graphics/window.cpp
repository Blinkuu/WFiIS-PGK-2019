//
// Created by blinku on 15.03.19.
//

#include <iostream>
#include "window.hpp"
#include "application.hpp"
#include "input_manager.hpp"

Window* Window::m_Instance = nullptr;

Window::Window()
    : m_RenderWindow(sf::RenderWindow{sf::VideoMode(800, 600), "Lab02"})
{
}

Window* Window::CreateWindow()
{
    if(!m_Instance)
        m_Instance = new Window{};
    return m_Instance;
}

void Window::RunEvents()
{
    while(m_RenderWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {
            Application::CloseApplication();
        }
        else if(event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                InputManager::SetMouseButtonPressedPosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                InputManager::SetMouseButtonDown(true);
                m_Canvas.UpdateCanvas();
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased)
        {
            InputManager::SetMouseButtonDown(false);
        }
    }

    if(InputManager::GetMouseButtonDown()) {
        InputManager::SetMouseButtonPressedPosition(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
    }
}

void Window::Clear()
{
    m_RenderWindow.clear(sf::Color::White);
}

void Window::Render()
{
    m_RenderWindow.draw(m_Canvas);
}

void Window::Display()
{
    m_RenderWindow.display();
}

void Window::CloseWindow()
{
    m_RenderWindow.close();
}
