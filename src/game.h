#ifndef CATGAME_GAME_H
#define CATGAME_GAME_H


#include <SFML/Graphics.hpp>

class game {
public:
    static int start();

private:
    static void mainLoop();

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
    static sf::RenderWindow mainWindow;
};


#endif //CATGAME_GAME_H
