//
// Created by Alex on 05/02/2020.
//

#include "textureManager.h"
#include "../constants.h"

void textureManager::loadTexture(const std::string &filepath) {
    sf::Texture texture;
    texture.loadFromFile(filepath);

    this->textures[filepath] = texture;
}

void textureManager::loadFont(const std::string &filepath) {
    sf::Font font;
    font.loadFromFile(filepath);

    this->fonts[filepath] = font;
}

sf::Texture& textureManager::getTexture(const std::string &texture) {
    return this->textures[texture];
}

sf::Font& textureManager::getFont(const std::string &font) {
    return this->fonts[font];
}

textureManager::textureManager() {
    loadFont(FONT_DEFAULT);

    loadTexture(SPRITE_PLAYER_DEFAULT);
    loadTexture(SPRITE_TILE_DEFAULT);
}
