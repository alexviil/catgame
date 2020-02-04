#ifndef CATGAME_GAME_H
#define CATGAME_GAME_H


#include <SFML/Graphics.hpp>
#include "world/world.h"
#include "draw.h"
#include "actor/actor.h"
#include "actor/player.h"

class game {
public:
    static int start();

private:
    static void mainLoop(player* player);

    /* uninitialized    loading assets or waiting for initialization
     * showingSplash    welcome screen
     * paused           ...
     * showingMenu
     * mainMenu
     * playing
     * exitPreparation
     * exiting
     */
    enum state {uninitialized, showingSplash, paused, showingMenu, mainMenu, playing, exitPreparation, exiting};

    static state gameState;
    static world gameWorld;
    static std::vector<actor*> actors;

    static sf::RenderWindow mainWindow;
    static sf::Clock movementClock;
};


#endif //CATGAME_GAME_H
