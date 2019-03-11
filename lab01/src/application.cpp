//
// Created by blinku on 09.03.19.
//

#include <iostream>
#include "application.h"

float Application::mouse_X;
float Application::mouse_Y;

Application::Application()
    : m_RenderWindow(sf::VideoMode{800, 650}, "GFK Lab 01", sf::Style::Titlebar | sf::Style::Close)
    , m_Event(sf::Event{})
    , m_Menu(Menu{})
    , m_Canvas(Canvas{})
{
    m_RenderWindow.setFramerateLimit(60);
}

void Application::run() {
    while (m_RenderWindow.isOpen()) {
        m_RenderWindow.clear(sf::Color::Black);

        while (m_RenderWindow.pollEvent(m_Event)) {
            m_Menu.run_event(m_Event, m_RenderWindow);
            m_Canvas.run_event(m_Event);
        }

        m_Canvas.set_mode(m_Menu.get_mode());

        m_RenderWindow.draw(m_Canvas);
        m_RenderWindow.draw(m_Menu);

        m_RenderWindow.display();
    }
}

void Application::set_mouse_pos(float x, float y) {
    mouse_X = x;
    mouse_Y = y;
}

void Application::print_debug_info() const {
    std::cout << "[" << mouse_X << ", " << mouse_Y << "]" << std::endl;
}