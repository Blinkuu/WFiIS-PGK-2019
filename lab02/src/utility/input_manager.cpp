//
// Created by blinku on 16.03.19.
//

#include "input_manager.hpp"

std::pair<float, float> InputManager::m_MouseButtonPressedPos{};
bool InputManager::m_MouseButtonDown = false;

void InputManager::SetMouseButtonPressedPosition(float x, float y)
{
    m_MouseButtonPressedPos.first = x;
    m_MouseButtonPressedPos.second = y;
}

void InputManager::SetMouseButtonDown(bool isDown)
{
    m_MouseButtonDown = isDown;
}

const std::pair<float, float>& InputManager::GetMouseButtonPressedPosition()
{
    return m_MouseButtonPressedPos;
}

bool InputManager::GetMouseButtonDown()
{
    return m_MouseButtonDown;
}
