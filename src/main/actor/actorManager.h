#ifndef CATGAME_ACTORMANAGER_H
#define CATGAME_ACTORMANAGER_H


#include "actor.h"
#include "player.h"
#include <SFML/Graphics/View.hpp>

class actorManager {
public:
    actorManager();

    player* createPlayer(float, float, sf::Texture&);
    void createActor(float, float, sf::Texture&);
    void removeActor(int i);
    void sortActorsByY();
    std::vector<actor*> &getActors();

private:
    std::vector<actor*> actors;
};


#endif //CATGAME_ACTORMANAGER_H
