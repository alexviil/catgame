#ifndef CATGAME_TEXTUREMANAGER_H
#define CATGAME_TEXTUREMANAGER_H


#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

class textureManager {
public:
    void loadTexture(const std::string&);
    void loadFont(const std::string&);
    sf::Texture& getTexture(const std::string&);
    sf::Font& getFont(const std::string&);

    textureManager();

private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
};


#endif //CATGAME_TEXTUREMANAGER_H
