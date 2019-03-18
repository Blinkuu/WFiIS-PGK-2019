//
// Created by blinku on 15.03.19.
//

#include <iostream>
#include "canvas.hpp"
#include "input_manager.hpp"

float Canvas::m_FormerSliderValue = 1.0f;

void Canvas::draw(sf::RenderTarget& target, [[maybe_unused]]sf::RenderStates states) const
{
    if(InputManager::GetMouseButtonDown()) {
        UpdateCanvas();
    }

    m_FPSCounter.Update();

    target.draw(m_Slider);
    target.draw(m_FPSCounter);
    target.draw(m_HSLCircle);
    target.draw(m_HSVCircle);
    target.draw(m_RGBCircle);
    target.draw(m_CMYCircle);
}

void Canvas::UpdateCanvas() const
{
    if(m_Slider.UpdateSlider() && fabs(m_FormerSliderValue - Slider::GetSliderValue()) > 0.0005)
    {
        m_FormerSliderValue = Slider::GetSliderValue();
        m_HSLCircle.Update();
        m_HSVCircle.Update();
        m_RGBCircle.Update();
        m_CMYCircle.Update();
    }
}
