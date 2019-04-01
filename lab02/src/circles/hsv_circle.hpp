//
// Created by blinku on 16.03.19.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "circle.hpp"

class HSVCircle : public Circle
{
public:
    HSVCircle();
    ~HSVCircle() override = default;

    void Update() override;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void convert(std::array<float, 3>& dest, const std::array<float, 3>& hsv) noexcept;
private:
    std::array<float, 3> m_HSV;
    std::array<float, 3> m_RGB;
};
