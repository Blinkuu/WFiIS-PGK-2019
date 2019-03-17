//
// Created by blinku on 15.03.19.
//

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "hsv_circle.hpp"
#include "slider.hpp"

HSVCircle::HSVCircle()
{
    sf::Vector2f circleCenter{static_cast<float>(m_TexSize) / 2.0f, static_cast<float>(m_TexSize) / 2.0f};
    float radiusMax = static_cast<float>(m_TexSize) * sqrtf(2.0f) / 2.8f;

    for(unsigned j = 0; j < m_TexSize; ++j)
        for(unsigned i = 0; i < m_TexSize; ++i)
        {
            sf::Vector2f radiusVec{i - circleCenter.x, j - circleCenter.y};
            float h = fmodf(atan2f(radiusVec.x, radiusVec.y) * 180.0f / static_cast<float>(M_PI) + 270.0f, 360.0f) / 360.0f;
            float s = sqrtf(radiusVec.x * radiusVec.x + radiusVec.y * radiusVec.y) / radiusMax;
            float v = 1.0f - Slider::GetSliderValue();

            m_TanSqrtArray[2 * (j * m_TexSize + i) + 0] = h;
            m_TanSqrtArray[2 * (j * m_TexSize + i) + 1] = s;

            m_HSV = {h, s, v};
            convert(m_RGB, m_HSV);

            m_ColorPixels[4 * (j * m_TexSize + i) + 0] = static_cast<sf::Uint8>(m_RGB[0]);
            m_ColorPixels[4 * (j * m_TexSize + i) + 1] = static_cast<sf::Uint8>(m_RGB[1]);
            m_ColorPixels[4 * (j * m_TexSize + i) + 2] = static_cast<sf::Uint8>(m_RGB[2]);
            m_ColorPixels[4 * (j * m_TexSize + i) + 3] = static_cast<sf::Uint8>(255);
        }

    m_Texture->update(m_ColorPixels);
    m_CircleShape.setTexture(m_Texture);
    m_CircleShape.setPosition(m_OffsetX + 350, m_OffsetY + 25);

    m_Text.setString("HSV");
    m_Text.setPosition(m_OffsetX + 350, m_OffsetY + 25);

    m_TextValue.setString("V=0.000");
    m_TextValue.setPosition(m_OffsetX + 440 + m_Radius, m_OffsetY + 25 + 2 * m_Radius - 12);
}

void HSVCircle::draw(sf::RenderTarget& target, [[maybe_unused]]sf::RenderStates states) const
{
    target.draw(m_Text);
    target.draw(m_TextValue);
    target.draw(m_CircleShape);
}

void HSVCircle::Update()
{
    for(unsigned j = 0; j < m_TexSize; ++j)
        for(unsigned i = 0; i < m_TexSize; ++i)
        {
            m_HSV[0] = m_TanSqrtArray[2 * (j * m_TexSize + i) + 0];
            m_HSV[1] = m_TanSqrtArray[2 * (j * m_TexSize + i) + 1];
            m_HSV[2] = 1.0f - Slider::GetSliderValue();

            convert(m_RGB, m_HSV);

            m_ColorPixels[4 * (j * m_TexSize + i) + 0] = static_cast<sf::Uint8>(m_RGB[0]);
            m_ColorPixels[4 * (j * m_TexSize + i) + 1] = static_cast<sf::Uint8>(m_RGB[1]);
            m_ColorPixels[4 * (j * m_TexSize + i) + 2] = static_cast<sf::Uint8>(m_RGB[2]);
        }
    m_Texture->update(m_ColorPixels);
    std::stringstream stream;
    stream << std::fixed << std::setprecision(3) << 1.0f - Slider::GetSliderValue();
    m_TextValue.setString("L=" + stream.str());
}

void HSVCircle::convert(std::array<float, 3>& dest, const std::array<float, 3>& hsv) noexcept
{
    if(hsv[1] == 0.0f)
    {
        dest[0] = 255.0f * hsv[2];
        dest[1] = 255.0f * hsv[2];
        dest[2] = 255.0f * hsv[2];
    } else
    {
        float h = hsv[0] * 6.0f;
        if(h == 6.0f) h = 0;
        float i = static_cast<int>(h);
        float var_1 = hsv[2] * (1 - hsv[1]);
        float var_2 = hsv[2] * (1 - hsv[1] * (h - i));
        float var_3 = hsv[2] * (1 - hsv[1] * (1 - (h - i)));

        float var_r;
        float var_g;
        float var_b;

        if      ( i == 0 ) { var_r = hsv[2]; var_g = var_3 ; var_b = var_1 ;}
        else if ( i == 1 ) { var_r = var_2 ; var_g = hsv[2]; var_b = var_1 ;}
        else if ( i == 2 ) { var_r = var_1 ; var_g = hsv[2]; var_b = var_3 ;}
        else if ( i == 3 ) { var_r = var_1 ; var_g = var_2 ; var_b = hsv[2];}
        else if ( i == 4 ) { var_r = var_3 ; var_g = var_1 ; var_b = hsv[2];}
        else               { var_r = hsv[2]; var_g = var_1 ; var_b = var_2 ;}

        dest[0] = var_r * 255.0f;
        dest[1] = var_g * 255.0f;
        dest[2] = var_b * 255.0f;
    }
}
