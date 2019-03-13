//
// Created by blinku on 09.03.19.
//

#include <iostream>
#include "file_manager.h"

sf::Texture* FileManager::m_TexturePtr = nullptr;

void FileManager::save_to_file(const std::vector<sf::Drawable*>& vec) {
    sf::RenderTexture renderTexture;
    //renderTexture.create(794, 534);
    renderTexture.create(800, 600);
    renderTexture.clear(sf::Color::Black);

    for (auto& x : vec) {
        renderTexture.draw(*x);
    }

    renderTexture.display();

    renderTexture.getTexture().copyToImage().saveToFile("Result.png");
}

sf::Sprite* FileManager::read_from_file(const std::string& filepath) {
    sf::Image image;
    image.loadFromFile(filepath);

    m_TexturePtr = new sf::Texture;
    m_TexturePtr->loadFromImage(image);

    sf::Sprite* spr = new sf::Sprite(*m_TexturePtr);

    return spr;
}
