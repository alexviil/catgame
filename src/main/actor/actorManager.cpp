#include <iostream>
#include "actorManager.h"

actorManager::actorManager() = default;

player* actorManager::createPlayer(float x, float y, sf::Texture& texture) {
    static player player(x, y, 25.f, texture);
    actors.push_back(&player);
    return &player;
}

void actorManager::createActor(float x, float y, sf::Texture& texture) {
    actors.push_back(new actor(x, y, 25.f, texture));
}

void actorManager::removeActor(int i) {
    actor* deletable = actors[i];
    actors.erase(actors.begin() + i);
    delete deletable;
    actors.shrink_to_fit();
}

std::vector<actor*> &actorManager::getActors() {
    return actors;
}

void actorManager::sortActorsByY() {
    std::sort(actors.begin(), actors.end(), [](actor* a1, actor* a2){
        return a1->getY() < (a2)->getY();
    });
}


