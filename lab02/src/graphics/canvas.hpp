//
// Created by blinku on 15.03.19.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <widgets/fps_counter.hpp>
#include "slider.hpp"
#include "fps_counter.hpp"
#include "hsl_circle.hpp"
#include "hsv_circle.hpp"
#include "cmy_circle.hpp"
#include "rgb_circle.hpp"

class Canvas : public sf::Drawable
{
public:
    Canvas() = default;
    ~Canvas() override = default;

    void UpdateCanvas() const;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    mutable Slider m_Slider;
    mutable FPSCounter m_FPSCounter;
    mutable HSLCircle m_HSLCircle;
    mutable HSVCircle m_HSVCircle;
    mutable RGBCircle m_RGBCircle;
    mutable CMYCircle m_CMYCircle;
};
