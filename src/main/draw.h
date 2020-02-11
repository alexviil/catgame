#pragma once
#ifndef CATGAME_DRAW_H
#define CATGAME_DRAW_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "world/world.h"
#include "actor/actor.h"
#include "actor/textContainer.h"

class draw {
public:
    static void render(sf::View&, world&, sf::RenderWindow&, std::vector<actor*>&, std::vector<textContainer*>&);
};


#endif //CATGAME_DRAW_H
