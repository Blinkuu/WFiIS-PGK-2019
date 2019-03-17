//
// Created by blinku on 15.03.19.
//

#include <cmath>
#include "circle.hpp"

Circle::Circle()
    : m_CircleShape(sf::CircleShape{})
    , m_Text(sf::Text{})
    , m_TextValue(sf::Text{})
    , m_Font(sf::Font{})
    , m_Radius(125.0f)
    , m_OffsetX(0.0f)
    , m_OffsetY(0.0f)
{
    m_Font.loadFromFile("fonts/Lato-Regular.ttf");
    m_Text.setFont(m_Font);
    m_Text.setCharacterSize(12);
    m_Text.setFillColor(sf::Color::Black);

    m_TextValue.setFont(m_Font);
    m_TextValue.setCharacterSize(12);
    m_TextValue.setFillColor(sf::Color::Black);

    m_CircleShape.setRadius(m_Radius);
    m_CircleShape.setPosition(m_OffsetX, m_OffsetY);
    m_CircleShape.setOutlineColor(sf::Color::Transparent);

    m_TexSize = static_cast<unsigned>(m_Radius * 2.0f / sqrtf(2.0f));
    m_ColorPixels = new sf::Uint8[m_TexSize * m_TexSize * 4];
    m_TanSqrtArray = new float[m_TexSize * m_TexSize * 2];

    m_Texture = new sf::Texture{};
    m_Texture->create(m_TexSize, m_TexSize);
}

Circle::~Circle()
{
    delete[] m_TanSqrtArray;
    delete[] m_ColorPixels;
    delete m_Texture;
}
