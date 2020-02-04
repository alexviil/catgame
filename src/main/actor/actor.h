#ifndef CATGAME_ACTOR_H
#define CATGAME_ACTOR_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class actor {
public:
    actor(float x, float y, float speed, sf::Texture *currentTexture);

    const sf::Sprite &getSprite() const;

protected:
    float x;
    float y;
    float speed;

    sf::Sprite sprite;

private:
    /*
    int hp;
    int armor;
    int dmg;
    ...
    */

    sf::Texture* currentTexture;

    /* TODO
    std::vector<std::string> idleTextures;
    std::vector<std::string> moveTextures;
    std::vector<std::string> jumpTextures;
    std::vector<std::string> useItemTextures;
    std::vector<std::string> attack1Textures;
    std::vector<std::string> attack2Textures;
    ...
    */
};


#endif //CATGAME_ACTOR_H
