//
// Created by blinku on 16.03.19.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "circle.hpp"

class CMYCircle : public Circle
{
public:
    CMYCircle();
    ~CMYCircle() override = default;

    void Update() override;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

