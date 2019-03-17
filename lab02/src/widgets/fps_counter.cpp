//
// Created by blinku on 16.03.19.
//

#include "fps_counter.hpp"

FPSCounter::FPSCounter()
    : m_Clock(sf::Clock{})
    , m_Frame(0)
    , m_FPS(0)
    , m_Text(sf::Text{})
    , m_Font(sf::Font{})
    , m_OffsetX(650)
    , m_OffsetY(350)
{
    m_Clock.restart();
    m_Font.loadFromFile("fonts/Lato-Regular.ttf");
    m_Text.setFont(m_Font);
    m_Text.setCharacterSize(12);
    m_Text.setFillColor(sf::Color::Black);
    m_Text.setString("FPS: 0");
    m_Text.setPosition(m_OffsetX, m_OffsetY);
}

void FPSCounter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    m_Text.setString("FPS: " + std::to_string(m_FPS));
    target.draw(m_Text);
}

void FPSCounter::Update()
{
    if(m_Clock.getElapsedTime().asSeconds() >= 1.0f)
    {
        m_FPS = m_Frame;
        m_Frame = 0;
        m_Clock.restart();
    }

    ++m_Frame;
}

unsigned int FPSCounter::GetFPS() const
{
    return m_FPS;
}
