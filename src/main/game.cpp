#include "game.h"
#include "../constants.h"
#include "world/world.h"
#include "draw.h"
#include "actor/actor.h"
#include "actor/player.h"
#include <iostream>

game::state game::gameState = uninitialized;
world game::gameWorld;
std::vector<actor*> game::actors;

sf::RenderWindow game::mainWindow;
sf::Clock game::movementClock;

int game::start() {
    std::cout << "Starting..." << std::endl;
    mainWindow.create(sf::VideoMode(1280, 720, 32), "Cat Game Project!");
    //mainWindow.setFramerateLimit(60);
    mainWindow.setVerticalSyncEnabled(true);

    // TODO move to actorManager.h
    sf::Texture player_default;
    player_default.loadFromFile(SPRITE_PLAYER_DEFAULT);
    player player(300.f, 300.f, 240.f, &player_default);
    actors.push_back(&player);

    gameState = playing;
    while(gameState != exiting) {
        try {
            mainLoop(&player);
        } catch (int e) {
            return e;
        }
    }

    std::cout << "Closing..." << std::endl;
    mainWindow.close();

    return 0;
}

void game::mainLoop(player* player) {
    sf::Event currentEvent{};
    while(mainWindow.pollEvent(currentEvent)) {

        switch (currentEvent.type) {
            case sf::Event::Closed:
                gameState = exiting;
                break;
            case sf::Event::KeyPressed:
                switch (currentEvent.key.code) {
                    case sf::Keyboard::W:
                        player->movingUp = true;
                        break;
                    case sf::Keyboard::A:
                        player->movingLeft = true;
                        break;
                    case sf::Keyboard::S:
                        player->movingDown = true;
                        break;
                    case sf::Keyboard::D:
                        player->movingRight = true;
                        break;
                }
                movementClock.restart();
                break;
            case sf::Event::KeyReleased:
                switch (currentEvent.key.code) {
                    case sf::Keyboard::W:
                        player->movingUp = false;
                        break;
                    case sf::Keyboard::A:
                        player->movingLeft = false;
                        break;
                    case sf::Keyboard::S:
                        player->movingDown = false;
                        break;
                    case sf::Keyboard::D:
                        player->movingRight = false;
                        break;
                }
                break;
        }
    }
    player->move(movementClock.restart().asSeconds());
    draw::render(&gameWorld, &mainWindow, &actors);
}