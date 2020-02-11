#include "actorManager.h"

actorManager::actorManager() = default;

player* actorManager::createPlayer(float x, float y, sf::Texture& texture) {
    static player player(x, y, 50.f, texture);
    actors.push_back(&player);
    return &player;
}

void actorManager::createActor(float x, float y, sf::Texture& texture) {
    static actor actor(x, y, 50.f, texture);
    actors.push_back(&actor);
}

void actorManager::removeActor(int i) {
    actors.erase(actors.begin() + i);
    actors.shrink_to_fit();
}

std::vector<actor*> &actorManager::getActors() {
    return actors;
}
