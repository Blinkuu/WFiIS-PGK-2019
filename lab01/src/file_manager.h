//
// Created by blinku on 09.03.19.
//

#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class FileManager {
public:
    static void save_to_file(const std::vector<sf::Drawable*>& vec);
    static sf::Texture read_from_file(const std::string& filepath);
};

