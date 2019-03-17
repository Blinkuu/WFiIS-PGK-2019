//
// Created by blinku on 15.03.19.
//

#pragma once

#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>

class Circle : public sf::Drawable
{
public:
    Circle();
    ~Circle() override;

    virtual void Update() = 0;

protected:
    sf::CircleShape m_CircleShape;
    sf::Text m_Text;
    sf::Text m_TextValue;
    sf::Font m_Font;
    sf::Texture* m_Texture;
    sf::Uint8* m_ColorPixels;
    float* m_TanSqrtArray;
    float m_Radius;
    float m_OffsetX;
    float m_OffsetY;
    unsigned m_TexSize;
};
