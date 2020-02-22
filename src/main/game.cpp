#include <iostream>
#include "game.h"
#include "../constants.h"
#include "draw.h"
#include "actor/actor.h"
#include "actor/player.h"
#include "actor/textContainer.h"

game::state game::gameState = uninitialized;
std::vector<textContainer*> game::texts;

actorManager game::actorManager;
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
    float ZOOM = 0.5f;
    mainView.zoom(ZOOM);
    mainWindow.setView(mainView);

    // Create debug texts;
    textContainer fps = textContainer(2.f, 2.f, textureManager.getFont(FONT_DEFAULT), "FPS: 0", 16);
    texts.push_back(&fps);
    int frames = 0;

    // Custom cursor
    float mouseX = 0, mouseY = 0;
    mainWindow.setMouseCursorVisible(false);
    sf::Sprite cursor;
    cursor.setTexture(textureManager.getTexture(SPRITE_CURSOR_ATTACK));
    cursor.scale(1.5f, 1.5f);

    // ---------- Game ----------

    player *player = actorManager.createPlayer(616.f, 336.f, textureManager.getTexture(SPRITE_PLAYER_DEFAULT));

    actorManager.createActor(400.f, 400.f, textureManager.getTexture(SPRITE_PLAYER_DEFAULT));
    actorManager.createActor(490.f, 380.f, textureManager.getTexture(SPRITE_PLAYER_DEFAULT));
    actorManager.createActor(200.f, 400.f, textureManager.getTexture(SPRITE_PLAYER_DEFAULT));
    actorManager.createActor(600.f, 400.f, textureManager.getTexture(SPRITE_PLAYER_DEFAULT));
    sf::Clock tempclock;

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
                                player->setInputMovingUp(true);
                                break;
                            case sf::Keyboard::A:
                                player->setInputMovingLeft(true);
                                break;
                            case sf::Keyboard::S:
                                player->setInputMovingDown(true);
                                break;
                            case sf::Keyboard::D:
                                player->setInputMovingRight(true);
                                break;
                        }
                        break;
                    case sf::Event::KeyReleased:
                        switch (currentEvent.key.code) {
                            case sf::Keyboard::W:
                                player->setInputMovingUp(false);
                                break;
                            case sf::Keyboard::A:
                                player->setInputMovingLeft(false);
                                break;
                            case sf::Keyboard::S:
                                player->setInputMovingDown(false);
                                break;
                            case sf::Keyboard::D:
                                player->setInputMovingRight(false);
                                break;
                        }
                        break;

                        // MOUSE PRESS/RELEASE

                    case sf::Event::MouseButtonPressed:
                        switch (currentEvent.mouseButton.button) {
                            case sf::Mouse::Left:
                                player->lookAt(mainView.getCenter().x - mainView.getSize().x / 2 + mouseX * ZOOM,
                                               mainView.getCenter().y - mainView.getSize().y / 2 + mouseY * ZOOM);
                                player->attack();
                                break;
                        }
                        break;
                    case sf::Event::MouseButtonReleased:
                        switch (currentEvent.mouseButton.button) {
                            case sf::Mouse::Left:
                                break;
                        }
                        break;

                        // MOUSE MOVED

                    case sf::Event::MouseMoved:
                        mouseX = currentEvent.mouseMove.x;
                        mouseY = currentEvent.mouseMove.y;
                        break;
                }
            }
            player->move(mainView, gameWorld, actorManager.getActors());
            mainWindow.setView(mainView);

            
            if (tempclock.getElapsedTime().asSeconds() > 0.5f) {
                for (int i = 0; i < actorManager.getActors().size(); ++i) {
                    if (actorManager.getActors()[i] != player) {
                        actorManager.getActors()[i]->move(true, false, false, false, gameWorld, actorManager.getActors());
                    }
                }
                if (tempclock.getElapsedTime().asSeconds() > 0.8f) {
                    tempclock.restart();
                }
            } else {
                for (int i = 0; i < actorManager.getActors().size(); ++i) {
                    if (actorManager.getActors()[i] != player) {
                        actorManager.getActors()[i]->move(false, false, true, false, gameWorld, actorManager.getActors());
                    }
                }
            }
            
            
            frames++;
            if (debugClock.getElapsedTime().asSeconds() > 1.f) {
                fps.getText().setString("FPS: " + std::to_string(frames));
                frames = 0;
                debugClock.restart();
            }

            fps.getText().setPosition(mainView.getCenter().x - mainView.getSize().x / 2 + 1, mainView.getCenter().y - mainView.getSize().y / 2 + 1);

            actorManager.sortActorsByY();
            draw::render(mainView, gameWorld, mainWindow, actorManager.getActors(), texts);

            cursor.setPosition(mainView.getCenter().x - mainView.getSize().x / 2 + mouseX * ZOOM,
                               mainView.getCenter().y - mainView.getSize().y / 2 + mouseY * ZOOM);
            mainWindow.draw(cursor);

            mainWindow.display();
        } catch (int e) {
            return e;
        }
    }

    // ---- Closing & Saving ----

    // todo save game state

    mainWindow.close();
    return 0;
}