//
// Created by blinku on 15.03.19.
//

#include <iostream>
#include <cmath>
#include "rgb_circle.hpp"
#include "slider.hpp"

RGBCircle::RGBCircle()
{
    sf::Vector2 circleCenter{static_cast<float>(m_TexSize) / 2.0f, static_cast<float>(m_TexSize) / 2.0f};
    float radiusMax = static_cast<float>(m_TexSize) * sqrtf(2.0f) / 2.8f;

    for(unsigned i = 0; i < m_TexSize; ++i)
        for(unsigned j = 0; j < m_TexSize; ++j)
        {
            sf::Vector2f radiusVec{static_cast<float>(i) - circleCenter.x, static_cast<float>(j) - circleCenter.y};

            float r = 255.0f * (1.0f - sqrtf(radiusVec.x * radiusVec.x + radiusVec.y * radiusVec.y) / radiusMax);
            float g = 255.0f * ((180.0f * atan2f(radiusVec.y, radiusVec.x) / static_cast<float>(M_PI)) + 361.0f) / 360.0f;
            float b = 255.0f * Slider::GetSliderValue();

            m_ColorPixels[4 * (j * m_TexSize + i) + 0] = static_cast<sf::Uint8>(255.0f - r);
            m_ColorPixels[4 * (j * m_TexSize + i) + 1] = static_cast<sf::Uint8>(255.0f - g);
            m_ColorPixels[4 * (j * m_TexSize + i) + 2] = static_cast<sf::Uint8>(255.0f - b);
            m_ColorPixels[4 * (j * m_TexSize + i) + 3] = static_cast<sf::Uint8>(255);
        }

    m_Texture->update(m_ColorPixels);
    m_CircleShape.setTexture(m_Texture);
    m_CircleShape.setPosition(m_OffsetX + 350, m_OffsetY + 325);

    m_Text.setString("RGB");
    m_Text.setPosition(m_OffsetX + 350, m_OffsetY + 325);

    m_TextValue.setString("B = 0");
    m_TextValue.setPosition(m_OffsetX + 350 + 2 * m_Radius - 35, m_OffsetY + 325 + 2 * m_Radius - 12);
}

void RGBCircle::draw(sf::RenderTarget& target, [[maybe_unused]]sf::RenderStates states) const
{
    target.draw(m_Text);
    target.draw(m_TextValue);
    target.draw(m_CircleShape);
}

void RGBCircle::Update()
{
    float b = 255.0f * Slider::GetSliderValue();
    for(unsigned i = 0; i < m_TexSize; ++i)
        for(unsigned j = 0; j < m_TexSize; ++j)
            m_ColorPixels[4 * (j * m_TexSize + i) + 2] = static_cast<sf::Uint8>(255.0f - b);

    m_Texture->update(m_ColorPixels);
    m_TextValue.setString("B: " + std::to_string(static_cast<unsigned>(255.0f - b)));
}
