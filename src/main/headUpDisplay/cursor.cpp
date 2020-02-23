#include <SFML/Graphics/Texture.hpp>
#include "cursor.h"



const sf::Sprite &cursor::getSprite() const {
    return sprite;
}

cursor::cursor(std::vector<actor *> &actors, sf::View &view, const sf::Texture& texture) : actors(actors), view(view) {
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 12,12));
    sprite.scale(1.5f, 1.5f);
}

void cursor::updateCursor(float mouseX, float mouseY, float ZOOM) {
    float x = view.getCenter().x - view.getSize().x / 2 + mouseX * ZOOM;
    float y = view.getCenter().y - view.getSize().y / 2 + mouseY * ZOOM;
    sprite.setPosition(x, y);

    for(actor* actor : actors) {
        if (
        x > actor->getCollisionX1() && x < actor->getCollisionX2() &&
        y > actor->getCollisionY1() && y < actor->getCollisionY2()) {
            setState(actor->isHostile() ? states::attack : states::inspect);
            return;
        }
    }

    setState(states::idle);
}

void cursor::setState(cursor::states newState) {
    if (state != newState) {
        state = newState;
        sprite.setTextureRect(sf::IntRect(0, 12 * state, 12,12));
    }
}
