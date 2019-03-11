//
// Created by blinku on 09.03.19.
//

#include <iostream>
#include <cmath>
#include "canvas.h"
#include "application.h"

std::vector<sf::Drawable*> Canvas::m_RenderQueue;

Canvas::Canvas()
    : m_Drawable(nullptr), m_ShouldDraw(false), m_FormerMousePos(std::pair<float, float>{}) {}

Canvas::~Canvas() {
    if(!m_RenderQueue.empty()) {
        for (auto& x : m_RenderQueue)
            delete x;
        m_RenderQueue.clear();
    }

}

void Canvas::run_event(const sf::Event& e) {
    switch (e.type) {
        case sf::Event::MouseButtonPressed:
            m_ShouldDraw = true;
            m_FormerMousePos = Application::get_mouse_pos();
            break;
        case sf::Event::MouseButtonReleased:
            m_ShouldDraw = false;
            if(m_Drawable != nullptr)
                m_RenderQueue.push_back(m_Drawable);
            m_Drawable = nullptr;
            break;
        default:
            break;
    }
}

void Canvas::set_mode(Menu::Mode m) {
    m_Mode = m;
}

void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto& x : m_RenderQueue)
            target.draw(*x);

    const std::pair currMousePos = Application::get_mouse_pos();
    if (m_ShouldDraw) {
        if (m_Mode == Menu::Mode::DRAW_CIRCLE) {
            sf::CircleShape* circle;

            if (!m_Drawable) {
                circle = new sf::CircleShape;
            } else {
                circle = dynamic_cast<sf::CircleShape*>(m_Drawable);
            }

            auto radius = static_cast<float>(sqrt(pow(currMousePos.first - m_FormerMousePos.first, 2) +
                                                  pow(currMousePos.second - m_FormerMousePos.second, 2)));
            circle->setRadius(radius);
            circle->setOutlineColor(Menu::get_current_drawing_color());
            circle->setFillColor(sf::Color::Transparent);
            circle->setOutlineThickness(1);
            circle->setPosition(m_FormerMousePos.first, m_FormerMousePos.second);

            m_Drawable = circle;
            target.draw(*circle);
        }

        if (m_Mode == Menu::Mode::DRAW_LINE) {
            sf::VertexArray* line;

            if (!m_Drawable) {
                line = new sf::VertexArray(sf::LinesStrip, 2);
            } else {
                line = dynamic_cast<sf::VertexArray*>(m_Drawable);
            }

            (*line)[0].position = sf::Vector2f(m_FormerMousePos.first, m_FormerMousePos.second);
            (*line)[0].color = Menu::get_current_drawing_color();
            (*line)[1].position = sf::Vector2f(currMousePos.first, currMousePos.second);
            (*line)[1].color = Menu::get_current_drawing_color();

            m_Drawable = line;
            target.draw(*line);
        }

        if (m_Mode == Menu::Mode::DRAW_RECTANGLE) {
            sf::RectangleShape* rectangle;

            if (!m_Drawable) {
                rectangle = new sf::RectangleShape;
            } else {
                rectangle = dynamic_cast<sf::RectangleShape*>(m_Drawable);
            }

            rectangle->setSize(sf::Vector2f(currMousePos.first - m_FormerMousePos.first, currMousePos.second - m_FormerMousePos.second));
            rectangle->setFillColor(sf::Color::Transparent);
            rectangle->setOutlineColor(Menu::get_current_drawing_color());
            rectangle->setOutlineThickness(1.0f);
            rectangle->setPosition(m_FormerMousePos.first, m_FormerMousePos.second);

            m_Drawable = rectangle;
            target.draw(*rectangle);
        }

        if (m_Mode == Menu::Mode::DRAW_FILLED_RECTANGLE) {
            sf::RectangleShape* rectangle;

            if (!m_Drawable) {
                rectangle = new sf::RectangleShape;
            } else {
                rectangle = dynamic_cast<sf::RectangleShape*>(m_Drawable);
            }

            rectangle->setSize(sf::Vector2f(currMousePos.first - m_FormerMousePos.first, currMousePos.second - m_FormerMousePos.second));
            rectangle->setFillColor(Menu::get_current_inside_color());
            rectangle->setOutlineColor(Menu::get_current_drawing_color());
            rectangle->setOutlineThickness(1.0f);
            rectangle->setPosition(m_FormerMousePos.first, m_FormerMousePos.second);

            m_Drawable = rectangle;
            target.draw(*rectangle);
        }
    }
}

void Canvas::clear_render_queue() {
    if(!m_RenderQueue.empty()) {
        for (auto& x : m_RenderQueue)
            delete x;
        m_RenderQueue.clear();
    }
}

void Canvas::push_sprite_to_render_queue(sf::Sprite* spr) {
    m_RenderQueue.push_back(spr);
}

std::vector<sf::Drawable*> Canvas::get_render_queue() {
    return m_RenderQueue;
}
