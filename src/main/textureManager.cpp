#include "textureManager.h"
#include "../constants.h"

void textureManager::loadTexture(const std::string &filepath) {
    sf::Texture texture;
    texture.loadFromFile(filepath);

    textures[filepath] = texture;
}

void textureManager::loadFont(const std::string &filepath) {
    sf::Font font;
    font.loadFromFile(filepath);

    fonts[filepath] = font;
}

sf::Texture& textureManager::getTexture(const std::string &texture) {
    return textures[texture];
}

sf::Font& textureManager::getFont(const std::string &font) {
    return fonts[font];
}

textureManager::textureManager() {
    loadFont(FONT_DEFAULT);

    loadTexture(SPRITE_PLAYER_DEFAULT);
    loadTexture(SPRITE_TILE_DEFAULT);
    loadTexture(SPRITE_TILE_BOUNCY);
    loadTexture(SPRITE_CURSOR_ATTACK);
}
