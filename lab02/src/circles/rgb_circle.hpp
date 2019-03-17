//
// Created by blinku on 15.03.19.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "circle.hpp"

class RGBCircle : public Circle
{
public:
    RGBCircle();
    ~RGBCircle() override = default;

    void Update() override;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
