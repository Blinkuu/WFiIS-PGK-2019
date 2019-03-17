//
// Created by blinku on 15.03.19.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "canvas.hpp"

class Window
{
public:
    Window();

    ~Window() = default;

    void RunEvents();
    void Clear();
    void Render();
    void Display();

    static Window* CreateWindow();
    void CloseWindow();
private:
    Canvas m_Canvas;
private:
    sf::RenderWindow m_RenderWindow;
    sf::Event event;
private:
    static Window* m_Instance;
};
