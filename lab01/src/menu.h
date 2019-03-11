//
// Created by blinku on 09.03.19.
//

#pragma once

#include <utility>
#include <string>
#include <SFML/Graphics.hpp>

class Menu : public sf::Drawable {
public:
    enum class Mode {
        DRAWING_COLOR,
        INSIDE_COLOR,
        DRAW_LINE,
        DRAW_RECTANGLE,
        DRAW_FILLED_RECTANGLE,
        DRAW_CIRCLE,
        WRITE_TO_FILE,
        READ_FROM_FILE,
        EXIT
    };
public:
    Menu();
    ~Menu() override;

    void run_event(const sf::Event& e, sf::Window& win);
    inline Mode get_mode() const;
    static inline sf::Color get_current_drawing_color();
    static inline sf::Color get_current_inside_color();
private:
    void outtextxy(sf::RenderTarget& target, float x, float y, const wchar_t* str) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    inline void draw_to_color_pixels(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b);
    inline sf::Color get_pixel_color(std::pair<float, float> mousePos);
private:
    sf::Font font;
    sf::Text* text;
    sf::RectangleShape* rectangle;
    sf::Texture* colors_texture;
    sf::Sprite* colors_sprite;
    sf::Uint8* colors_pixels;
    const unsigned int colors_size_x = 765;
    const unsigned int colors_size_y = 60;

    Mode m_Mode;
    std::wstring m_ButtonPressed;
    static sf::Color m_CurrentDrawingColor;
    static sf::Color m_CurrentInsideColor;
    sf::RectangleShape* m_CurrentDrawingRec;
    sf::RectangleShape* m_CurrentInsideRec;
    sf::RectangleShape* m_Board;
};

inline void Menu::draw_to_color_pixels(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b) {
    colors_pixels[4 * (y * colors_size_x + x) + 0] = r;
    colors_pixels[4 * (y * colors_size_x + x) + 1] = g;
    colors_pixels[4 * (y * colors_size_x + x) + 2] = b;
    colors_pixels[4 * (y * colors_size_x + x) + 3] = 255;
}

inline sf::Color Menu::get_pixel_color(std::pair<float, float> mousePos) {
    if (mousePos.first > 0.0f && mousePos.first < colors_size_x && mousePos.second > 0.0f && mousePos.second < colors_size_y) {
        int r = static_cast<int>(colors_pixels[4 * (static_cast<int>(mousePos.second) *  colors_size_x + static_cast<int>(mousePos.first)) + 0]);
        int g = static_cast<int>(colors_pixels[4 * (static_cast<int>(mousePos.second) *  colors_size_x + static_cast<int>(mousePos.first)) + 1]);
        int b = static_cast<int>(colors_pixels[4 * (static_cast<int>(mousePos.second) *  colors_size_x + static_cast<int>(mousePos.first)) + 2]);
        return sf::Color(r, g, b);
    }
    return sf::Color::Transparent;
}

inline Menu::Mode Menu::get_mode() const {
    return m_Mode;
}

inline sf::Color Menu::get_current_drawing_color() {
    return m_CurrentDrawingColor;
}

inline sf::Color Menu::get_current_inside_color() {
    return m_CurrentInsideColor;
}
