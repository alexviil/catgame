#ifndef CATGAME_CURSOR_H
#define CATGAME_CURSOR_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>
#include "../actor/actor.h"

class cursor {
public:
    cursor(std::vector<actor *> &actors, sf::View &view, const sf::Texture&);

    void updateCursor(float, float, float);
    const sf::Sprite &getSprite() const;

private:
    enum states {idle, attack, inspect};

    void setState(cursor::states);

    cursor::states state = idle;
    std::vector<actor*>& actors;
    sf::View& view;
    sf::Sprite sprite;
};


#endif //CATGAME_CURSOR_H
