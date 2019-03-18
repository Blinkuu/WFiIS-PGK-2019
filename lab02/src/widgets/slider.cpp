//
// Created by blinku on 16.03.19.
//

#include <iostream>
#include "slider.hpp"
#include "input_manager.hpp"

float Slider::m_CurrentSliderValue = 1.0f;

Slider::Slider()
    : m_Bar(sf::RectangleShape{})
    , m_Line1(sf::VertexArray{sf::LinesStrip, 2})
    , m_Line2(sf::VertexArray{sf::LinesStrip, 2})
    , m_SizeX(50)
    , m_SizeY(302)
    , m_OffsetX(650)
    , m_OffsetY(25)
{

    m_Line1[0].position = sf::Vector2f(static_cast<float>(m_OffsetX) - 15.0f, static_cast<float>(m_OffsetY));
    m_Line1[0].color = sf::Color::Black;
    m_Line1[1].position = sf::Vector2f(static_cast<float>(m_OffsetX) - 5.0f, static_cast<float>(m_OffsetY));
    m_Line1[1].color = sf::Color::Black;

    m_Line2[0].position = sf::Vector2f(static_cast<float>(m_OffsetX + m_SizeX) + 5.0f, static_cast<float>(m_OffsetY));
    m_Line2[0].color = sf::Color::Black;
    m_Line2[1].position = sf::Vector2f(static_cast<float>(m_OffsetX + m_SizeX) + 15.0f, static_cast<float>(m_OffsetY));
    m_Line2[1].color = sf::Color::Black;

    m_Bar.setSize(sf::Vector2f(static_cast<float>(static_cast<float>(m_SizeX)), static_cast<float>(m_SizeY)));
    m_Bar.setPosition(static_cast<float>(m_OffsetX), static_cast<float>(m_OffsetY));
    m_Bar.setOutlineColor(sf::Color::Black);
    m_Bar.setOutlineThickness(1.0f);

    m_ColorPixels = new sf::Uint8[m_SizeX * m_SizeY * 4];

    for(unsigned j = 0; j < m_SizeX; ++j) {
        for(unsigned i = 0; i < m_SizeY; ++i)
        {
            float r = 0;
            float g = 0;
            float b = 0;
            float a = 255.0f - 255.0f * static_cast<float>(i) / static_cast<float>(m_SizeY);

            m_ColorPixels[4 * (i * m_SizeX + j) + 0] = static_cast<sf::Uint8>(r);
            m_ColorPixels[4 * (i * m_SizeX + j) + 1] = static_cast<sf::Uint8>(g);
            m_ColorPixels[4 * (i * m_SizeX + j) + 2] = static_cast<sf::Uint8>(b);
            m_ColorPixels[4 * (i * m_SizeX + j) + 3] = static_cast<sf::Uint8>(a);
        }
    }


    m_Texture = new sf::Texture{};
    m_Texture->create(m_SizeX, m_SizeY);
    m_Texture->update(m_ColorPixels);
    m_Bar.setTexture(m_Texture);
}

Slider::~Slider()
{
    delete[] m_ColorPixels;
    delete m_Texture;
}

void Slider::draw(sf::RenderTarget& target, [[maybe_unused]]sf::RenderStates states) const
{
    target.draw(m_Line1);
    target.draw(m_Line2);
    target.draw(m_Bar);
}

bool Slider::UpdateSlider()
{
    const std::pair<float, float>& mousePos = InputManager::GetMouseButtonPressedPosition();

    if((mousePos.first > m_OffsetX && mousePos.first < m_OffsetX + m_SizeX) && (mousePos.second > m_OffsetY && mousePos.second < m_SizeY + m_OffsetY))
    {
        float a = static_cast<float>(mousePos.second - m_OffsetY - 1) / static_cast<float>(m_SizeY - 2);
        m_CurrentSliderValue = 1.0f - a;
        m_Line1[0].position = sf::Vector2f(static_cast<float>(m_OffsetX) - 15.0f, mousePos.second);
        m_Line1[1].position = sf::Vector2f(static_cast<float>(m_OffsetX) - 5.0f, mousePos.second);
        m_Line2[0].position = sf::Vector2f(static_cast<float>(m_OffsetX + m_SizeX) + 5.0f, mousePos.second);
        m_Line2[1].position = sf::Vector2f(static_cast<float>(m_OffsetX + m_SizeX) + 15.0f, mousePos.second);
        return true;
    }
    return false;
}

float Slider::GetSliderValue()
{
    return m_CurrentSliderValue;
}
