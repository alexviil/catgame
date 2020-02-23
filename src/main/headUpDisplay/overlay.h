#ifndef CATGAME_OVERLAY_H
#define CATGAME_OVERLAY_H


#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../actor/player.h"
#include "../actor/textContainer.h"

class overlay {
public:
    overlay(sf::View &view, player *player, const sf::Texture&, const sf::Font& debugFont);

    void updateOverlay(float);
    void toggleDebug();
    void drawDebug(sf::RenderWindow&);

    const sf::Sprite &getSprite() const;

private:
    sf::Sprite sprite;
    sf::View& view;
    player* playerObject;
    bool showDebug = false;
    sf::Clock debugClock;
    int debugFrames = 0;
    std::vector<textContainer*> texts;

};


#endif //CATGAME_OVERLAY_H
