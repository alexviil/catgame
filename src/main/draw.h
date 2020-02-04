#ifndef CATGAME_DRAW_H
#define CATGAME_DRAW_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "world/world.h"
#include "actor/actor.h"

class draw {
public:
    static void render(world*, sf::RenderWindow*, std::vector<actor*>*);
};


#endif //CATGAME_DRAW_H
