//
// Created by blinku on 16.03.19.
//

#pragma once

#include <SFML/Graphics.hpp>

class FPSCounter : public sf::Drawable
{
public:
    FPSCounter();
    ~FPSCounter() override = default;

    void Update();
    unsigned int GetFPS() const;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::Clock m_Clock;
    unsigned int m_Frame;
    unsigned int m_FPS;

    mutable sf::Text m_Text;
    sf::Font m_Font;
    float m_OffsetX;
    float m_OffsetY;
};
