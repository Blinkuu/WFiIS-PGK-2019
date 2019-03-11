//
// Created by blinku on 09.03.19.
//

#include <utility>
#include <SFML/Graphics.hpp>
#include "menu.h"
#include "canvas.h"

#pragma once

class Application {
public:
    Application();
    ~Application() = default;

    void run();

    static void set_mouse_pos(float x, float y);
    static inline const std::pair<float, float> get_mouse_pos();
private:
    void print_debug_info() const;
private:
    sf::RenderWindow m_RenderWindow;
    sf::Event m_Event;
    Menu m_Menu;
    Canvas m_Canvas;

    static float mouse_X;
    static float mouse_Y;
};

inline const std::pair<float, float> Application::get_mouse_pos() {
    return std::make_pair(mouse_X, mouse_Y);
}