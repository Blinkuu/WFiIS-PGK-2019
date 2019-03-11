//
// Created by blinku on 09.03.19.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>
#include "menu.h"

class Canvas : public sf::Drawable {
public:
    Canvas();
    ~Canvas();

    void run_event(const sf::Event& e);
    void set_mode(Menu::Mode m);

    static void clear_render_queue();
    static void push_sprite_to_render_queue(sf::Sprite* spr);
    static std::vector<sf::Drawable*> get_render_queue();
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    Menu::Mode m_Mode;
    mutable sf::Drawable* m_Drawable;
    bool m_ShouldDraw;
    std::pair<float, float> m_FormerMousePos;
    static std::vector<sf::Drawable*> m_RenderQueue;
};

