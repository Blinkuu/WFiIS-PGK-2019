//
// Created by blinku on 16.03.19.
//

#pragma once

#include <utility>

class InputManager
{
public:
    static void SetMouseButtonPressedPosition(float x, float y);
    static void SetMouseButtonDown(bool isDown);

    static const std::pair<float, float>& GetMouseButtonPressedPosition();
    static bool GetMouseButtonDown();

private:
    static std::pair<float, float> m_MouseButtonPressedPos;
    static bool m_MouseButtonDown;
};
