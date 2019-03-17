//
// Created by blinku on 16.03.19.
//

#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include "circle.hpp"

class HSLCircle : public Circle
{
public:
    HSLCircle();
    ~HSLCircle() override = default;

    void Update() override;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void convert(std::array<float, 3>& dest, const std::array<float, 3>& col) noexcept;
private:
    std::array<float, 3> m_HSL;
    std::array<float, 3> m_RGB;
};
