//
// Created by blinku on 15.03.19.
//

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "hsl_circle.hpp"
#include "slider.hpp"

HSLCircle::HSLCircle()
{
    sf::Vector2f circleCenter{m_TexSize / 2.0f, m_TexSize / 2.0f};
    float radiusMax = m_TexSize * sqrtf(2.0f) / 2.8f;

    for(unsigned j = 0; j < m_TexSize; ++j)
        for(unsigned i = 0; i < m_TexSize; ++i)
        {
            sf::Vector2f radiusVec{i - circleCenter.x, j - circleCenter.y};
            float h = fmodf(atan2f(radiusVec.x, radiusVec.y) * 180.0f / static_cast<float>(M_PI) + 270.0f, 360.0f);
            float s = sqrtf(radiusVec.x * radiusVec.x + radiusVec.y * radiusVec.y) / radiusMax;
            float l = 1.0f - Slider::GetSliderValue();

            m_TanSqrtArray[2 * (j * m_TexSize + i) + 0] = h;
            m_TanSqrtArray[2 * (j * m_TexSize + i) + 1] = s;

            m_HSL = {h, s, l};
            convert(m_RGB, m_HSL);

            m_ColorPixels[4 * (j * m_TexSize + i) + 0] = static_cast<sf::Uint8>(m_RGB[0]);
            m_ColorPixels[4 * (j * m_TexSize + i) + 1] = static_cast<sf::Uint8>(m_RGB[1]);
            m_ColorPixels[4 * (j * m_TexSize + i) + 2] = static_cast<sf::Uint8>(m_RGB[2]);
            m_ColorPixels[4 * (j * m_TexSize + i) + 3] = static_cast<sf::Uint8>(255);
        }

    m_Texture->update(m_ColorPixels);
    m_CircleShape.setTexture(m_Texture);
    m_CircleShape.setPosition(m_OffsetX + 50, m_OffsetY + 25);

    m_Text.setString("HSL");
    m_Text.setPosition(m_OffsetX + 50, m_OffsetY + 25);

    m_TextValue.setString("L=0.000");
    m_TextValue.setPosition(m_OffsetX + 140 + m_Radius, m_OffsetY + 25 + 2 * m_Radius - 12);
}

void HSLCircle::draw(sf::RenderTarget& target, [[maybe_unused]]sf::RenderStates states) const
{
    target.draw(m_Text);
    target.draw(m_TextValue);
    target.draw(m_CircleShape);
}

void HSLCircle::Update()
{
    m_HSL[2] = 1.0f - Slider::GetSliderValue();
    for(unsigned j = 0; j < m_TexSize; ++j)
        for(unsigned i = 0; i < m_TexSize; ++i)
        {
            m_HSL[0] = m_TanSqrtArray[2 * (j * m_TexSize + i) + 0];
            m_HSL[1] = m_TanSqrtArray[2 * (j * m_TexSize + i) + 1];

            convert(m_RGB, m_HSL);

            m_ColorPixels[4 * (j * m_TexSize + i) + 0] = static_cast<sf::Uint8>(m_RGB[0]);
            m_ColorPixels[4 * (j * m_TexSize + i) + 1] = static_cast<sf::Uint8>(m_RGB[1]);
            m_ColorPixels[4 * (j * m_TexSize + i) + 2] = static_cast<sf::Uint8>(m_RGB[2]);
        }
    m_Texture->update(m_ColorPixels);

    std::stringstream stream;
    stream << std::fixed << std::setprecision(3) << m_HSL[2];
    m_TextValue.setString("L=" + stream.str());
}

void HSLCircle::convert(std::array<float, 3>& dest, const std::array<float, 3>& col) noexcept
{
    float C = ( 1.0f - fabsf(2.0f * col[2] - 1.0f)) * col[1];
    float X = C * ( 1.0f - fabsf(fmodf(col[0] * 0.016666f, 2.0f) - 1.0f));
    float m = col[2] - C / 2.0f;

    if (col[0] < 60) {
        dest[0] = ( C + m ) * 255;
        dest[1] = ( X + m ) * 255;
        dest[2] = ( 0 + m ) * 255;
    } else if (col[0] < 120) {
        dest[0] = ( X + m ) * 255;
        dest[1] = ( C + m ) * 255;
        dest[2] = ( 0 + m ) * 255;
    } else if (col[0] < 180) {
        dest[0] = ( 0 + m ) * 255;
        dest[1] = ( C + m ) * 255;
        dest[2] = ( X + m ) * 255;
    } else if (col[0] < 240) {
        dest[0] = ( 0 + m ) * 255;
        dest[1] = ( X + m ) * 255;
        dest[2] = ( C + m ) * 255;
    } else if (col[0] < 300) {
        dest[0] = ( X + m ) * 255;
        dest[1] = ( 0 + m ) * 255;
        dest[2] = ( C + m ) * 255;
    } else {
        dest[0] = ( C + m ) * 255;
        dest[1] = ( 0 + m ) * 255;
        dest[2] = ( X + m ) * 255;
    }
}