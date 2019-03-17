//
// Created by blinku on 16.03.19.
//

#pragma once

#include <SFML/Graphics.hpp>

class Slider : public sf::Drawable
{
public:
    Slider();
    ~Slider() override;

    bool UpdateSlider();
    static float GetSliderValue();
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::RectangleShape m_Bar;
    sf::VertexArray m_Line1;
    sf::VertexArray m_Line2;
    sf::Texture* m_Texture;
    sf::Uint8 *m_ColorPixels;
    unsigned m_SizeX;
    unsigned m_SizeY;
    unsigned m_OffsetX;
    unsigned m_OffsetY;
    static float m_CurrentSliderValue;
};
