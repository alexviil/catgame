#include <iostream>
#include "game.h"
#include "../constants.h"
#include "world/world.h"
#include "draw.h"
#include "actor/actor.h"
#include "actor/player.h"
#include "actor/textContainer.h"

game::state game::gameState = uninitialized;
std::vector<actor*> game::actors;
std::vector<textContainer*> game::texts;
textureManager game::textureManager;
world game::gameWorld(game::textureManager);

sf::Clock game::debugClock;
sf::RenderWindow game::mainWindow;

int game::start() {
    // ----- Initialization -----

    // Create window
    mainWindow.create(sf::VideoMode(1920, 1080, 32), "Cat Game Project!");
    mainWindow.setFramerateLimit(60);
    //mainWindow.setVerticalSyncEnabled(true);

    // Create view (optional, allows "camera" movement, panning, etc.)
    sf::View mainView = sf::View(sf::Vector2f(640.f, 360.f), sf::Vector2f(1920.f, 1080.f));
    mainView.zoom(0.5f);
    mainWindow.setView(mainView);

    // Create debug texts;
    textContainer fps = textContainer(2.f, 2.f, textureManager.getFont(FONT_DEFAULT), "FPS: 0", 16);
    texts.push_back(&fps);
    int frames = 0;

    // ---------- Game ----------

    //https://www.gamefromscratch.com/post/2015/10/26/SFML-CPP-Tutorial-Spritesheets-and-Animation.aspx

    player player(616.f, 336.f, 10.f, textureManager.getTexture(SPRITE_PLAYER_DEFAULT));
    actors.push_back(&player);

    // ------- Main Loop --------

    gameState = playing;
    while(gameState != exiting) {
        try {
            sf::Event currentEvent{};
            while(mainWindow.pollEvent(currentEvent)) {
                switch (currentEvent.type) {

                        // WINDOW CLOSED

                    case sf::Event::Closed:
                        gameState = exiting;
                        break;

                        // KEY PRESS/RELEASE

                    case sf::Event::KeyPressed:
                        switch (currentEvent.key.code) {
                            case sf::Keyboard::W:
                                player.setInputMovingUp(true);
                                break;
                            case sf::Keyboard::A:
                                player.setInputMovingLeft(true);
                                break;
                            case sf::Keyboard::S:
                                player.setInputMovingDown(true);
                                break;
                            case sf::Keyboard::D:
                                player.setInputMovingRight(true);
                                break;
                        }
                        break;
                    case sf::Event::KeyReleased:
                        switch (currentEvent.key.code) {
                            case sf::Keyboard::W:
                                player.setInputMovingUp(false);
                                break;
                            case sf::Keyboard::A:
                                player.setInputMovingLeft(false);
                                break;
                            case sf::Keyboard::S:
                                player.setInputMovingDown(false);
                                break;
                            case sf::Keyboard::D:
                                player.setInputMovingRight(false);
                                break;
                        }
                        break;

                }
            }

            player.move(mainView, gameWorld);
            mainWindow.setView(mainView);
            frames++;
            if (debugClock.getElapsedTime().asSeconds() >= 1.f) {
                fps.getText().setString("FPS: " + std::to_string(frames));
                debugClock.restart();
                frames = 0;
            }

            fps.getText().setPosition(mainView.getCenter().x - mainView.getSize().x / 2, mainView.getCenter().y - mainView.getSize().y / 2);
            draw::render(gameWorld, mainWindow, actors, texts);
        } catch (int e) {
            return e;
        }
    }

    // ---- Closing & Saving ----

    mainWindow.close();
    return 0;
}