#include "overlay.h"

overlay::overlay(sf::View &view, player* player, const sf::Texture& texture, const sf::Font& debugFont) : view(view), playerObject(player) {
    sprite.setTexture(texture);
    sprite.scale(2.f, 2.f);
    texts.push_back(new textContainer(2.f, 2.f, debugFont, "FPS:        0.0", 48));
    texts.push_back(new textContainer(2.f, 2.f, debugFont, "Player X: 0.0", 48));
    texts.push_back(new textContainer(2.f, 2.f, debugFont, "Player Y: 0.0", 48));
}

void overlay::updateOverlay(float ZOOM) {
    sprite.setPosition(view.getCenter().x + view.getSize().x / 2 * ZOOM - sprite.getTextureRect().width,
                       view.getCenter().y - view.getSize().y / 2);

    if (showDebug) {
        debugFrames++;

        float x = view.getCenter().x - view.getSize().x / 2 + 4;
        float y = view.getCenter().y - view.getSize().y / 2 + 4;

        texts[0]->getText().setPosition(x, y);
        texts[1]->getText().setPosition(x, y + 30);
        texts[2]->getText().setPosition(x, y + 60);

        if (debugClock.getElapsedTime().asSeconds() > 0.5f) {
            texts[0]->getText().setString("FPS:        " + std::to_string(float(debugFrames) / debugClock.restart().asSeconds()));
            texts[1]->getText().setString("Player X: " + std::to_string(playerObject->getCollisionCentreX()));
            texts[2]->getText().setString("Player Y: " + std::to_string(playerObject->getCollisionCentreY()));
            debugFrames = 0;
        }
    }
}

const sf::Sprite &overlay::getSprite() const {
    return sprite;
}

void overlay::toggleDebug() {
    showDebug = !showDebug;
}

void overlay::drawDebug(sf::RenderWindow& window) {
    if (showDebug) {
        for (int i = 0; i < texts.size(); ++i) {
            window.draw(texts[i]->getText());
        }
    }
}
