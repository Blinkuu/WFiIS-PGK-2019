// Created by blinku on 09.03.19.
//

#include <iostream>
#include <SFML/Window.hpp>
#include "application.h"
#include "menu.h"
#include "file_manager.h"
#include "font.h"

sf::Color Menu::m_CurrentDrawingColor = sf::Color::Transparent;
sf::Color Menu::m_CurrentInsideColor = sf::Color::Transparent;

Menu::Menu() {
    font.loadFromMemory(font_data, font_data_size);
    text = new sf::Text;
    text->setFont(font);
    text->setCharacterSize(12);
    text->setFillColor(sf::Color::White);

    rectangle = new sf::RectangleShape(sf::Vector2f(796, 536));
    rectangle->setFillColor(sf::Color::Transparent);
    rectangle->setOutlineColor(sf::Color::White);
    rectangle->setOutlineThickness(1.0f);
    rectangle->setPosition(2, 62);

    unsigned int x, y;
    colors_pixels = new sf::Uint8[colors_size_x * colors_size_y * 4];
    for (x = 0; x < 255; x++)
        for (y = 0; y < 30; y++) {
            draw_to_color_pixels(x, y, x, 255, 0);
            draw_to_color_pixels(x + 255, y, 255, 255 - x, 0);
            draw_to_color_pixels(x + 510, y, 255, 0, x);
            draw_to_color_pixels(254 - x, y + 30, 0, 255, 255 - x);
            draw_to_color_pixels(509 - x, y + 30, 0, x, 255);
            draw_to_color_pixels(764 - x, y + 30, 255 - x, 0, 255);
        }

    colors_texture = new sf::Texture();
    colors_texture->create(colors_size_x, colors_size_y);
    colors_texture->update(colors_pixels);

    colors_sprite = new sf::Sprite();
    colors_sprite->setTexture(*colors_texture);
    colors_sprite->setPosition(1, 1);

    m_CurrentDrawingRec = new sf::RectangleShape(sf::Vector2f(colors_size_y / 2.0f, colors_size_y / 2.0f));
    m_CurrentDrawingRec->setFillColor(sf::Color::Transparent);
    m_CurrentDrawingRec->setPosition(768, 0);

    m_CurrentInsideRec = new sf::RectangleShape(sf::Vector2f(colors_size_y / 2.0f, colors_size_y / 2.0f));
    m_CurrentInsideRec->setFillColor(sf::Color::Transparent);
    m_CurrentInsideRec->setPosition(768, 1 + colors_size_y / 2.0f);

    m_Board = new sf::RectangleShape(sf::Vector2f(800, 200));
    m_Board->setFillColor(sf::Color::Black);

    m_ButtonPressed = L"";
}

Menu::~Menu() {
    delete text;
    delete rectangle;
    delete colors_texture;
    delete colors_sprite;
    delete m_CurrentDrawingRec;
    delete m_CurrentInsideRec;
    delete m_Board;
}

void Menu::run_event(const sf::Event& e, sf::Window& win) {
    if (e.type == sf::Event::Closed)
        win.close();

    if (e.type == sf::Event::MouseMoved)
        Application::set_mouse_pos(e.mouseMove.x, e.mouseMove.y);

    if (e.type == sf::Event::KeyPressed) {
        switch (e.key.code) {
            case sf::Keyboard::F:
                m_Mode = Mode::DRAWING_COLOR;
                m_ButtonPressed = L"f";
                break;
            case sf::Keyboard::B:
                m_Mode = Mode::INSIDE_COLOR;
                m_ButtonPressed = L"b";
                break;
            case sf::Keyboard::L:
                m_Mode = Mode::DRAW_LINE;
                m_ButtonPressed = L"l";
                break;
            case sf::Keyboard::R:
                m_Mode = Mode::DRAW_RECTANGLE;
                m_ButtonPressed = L"r";
                break;
            case sf::Keyboard::A:
                m_Mode = Mode::DRAW_FILLED_RECTANGLE;
                m_ButtonPressed = L"a";
                break;
            case sf::Keyboard::C:
                m_Mode = Mode::DRAW_CIRCLE;
                m_ButtonPressed = L"c";
                break;
            case sf::Keyboard::W:
                m_Mode = Mode::WRITE_TO_FILE;
                m_ButtonPressed = L"w";
                FileManager::save_to_file(Canvas::get_render_queue());
                break;
            case sf::Keyboard::O:
            {
                m_Mode = Mode::READ_FROM_FILE;
                m_ButtonPressed = L"o";
                sf::Sprite* spr = FileManager::read_from_file("Result.png");
                Canvas::clear_render_queue();
                Canvas::push_sprite_to_render_queue(spr);
            }
                break;
            case sf::Keyboard::Escape:
                m_Mode = Mode::EXIT;
                win.close();
                break;
            default:
                break;
        }
    } else if (e.type == sf::Event::MouseButtonPressed) {
        if (m_Mode == Mode::DRAWING_COLOR) {
            m_CurrentDrawingColor = get_pixel_color(Application::get_mouse_pos());
            m_CurrentDrawingRec->setFillColor(m_CurrentDrawingColor);
        }
        else if (m_Mode == Mode::INSIDE_COLOR) {
            m_CurrentInsideColor = get_pixel_color(Application::get_mouse_pos());
            m_CurrentInsideRec->setFillColor(m_CurrentInsideColor);
        }
    }
}

void Menu::outtextxy(sf::RenderTarget& target, float x, float y, const wchar_t* str) const {
    text->setPosition(x, y);
    text->setString(str);
    target.draw(*text);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    m_Board->setPosition(0, 0);
    m_Board->setSize(sf::Vector2f(800.0f, 61.0f));
    target.draw(*m_Board);

    m_Board->setPosition(0, 598);
    m_Board->setSize(sf::Vector2f(800.0f, 600.0f));
    target.draw(*m_Board);

    outtextxy(target, 5, 600, L"f - wybór koloru rysowania");
    outtextxy(target, 5, 615, L"b - wybór koloru wypełnienia");
    outtextxy(target, 5, 630, L"l - rysowanie linii");

    outtextxy(target, 200, 600, L"r - rysowanie prostokąta");
    outtextxy(target, 200, 615, L"a - rysowanie wypełnionego prostokąta");
    outtextxy(target, 200, 630, L"c - rysowanie okręgu");

    outtextxy(target, 470, 600, L"w - zapis do pliku");
    outtextxy(target, 470, 615, L"o - odczyt z pliku");
    outtextxy(target, 470, 630, L"esc - wyjście");

    outtextxy(target, 650, 615, (std::wstring(L"Aktualne: ") + std::wstring(m_ButtonPressed)).c_str());

    target.draw(*m_CurrentDrawingRec);
    target.draw(*m_CurrentInsideRec);
    target.draw(*rectangle);
    target.draw(*colors_sprite);
}
