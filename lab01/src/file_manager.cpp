//
// Created by blinku on 09.03.19.
//

#include <iostream>
#include "file_manager.h"

void FileManager::save_to_file(const std::vector<sf::Drawable*>& vec) {
    sf::RenderTexture renderTexture;
    renderTexture.create(794, 534);
    renderTexture.clear(sf::Color::Black);

    for (auto& x : vec) {
        renderTexture.draw(*x);
    }

    renderTexture.display();

    renderTexture.getTexture().copyToImage().saveToFile("Result.png");
}

sf::Texture FileManager::read_from_file(const std::string& filepath) {
    sf::Image image;
    image.loadFromFile(filepath);

    sf::Texture texture;
    texture.loadFromImage(image);

    return texture;
}
