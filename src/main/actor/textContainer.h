#ifndef CATGAME_TEXTCONTAINER_H
#define CATGAME_TEXTCONTAINER_H


#include <SFML/Graphics/Text.hpp>

class textContainer {
public:
    textContainer(float x, float y, const sf::Font& font, const std::string& displayText, unsigned int size) {
        sf::Text newText;
        newText.setFont(font);
        newText.setPosition(x, y);
        newText.setString(displayText);
        newText.setCharacterSize(size);
        newText.setScale(0.5f, 0.5f);
        textContainer::text = newText;
    }

    sf::Text &getText(){
        return text;
    }

private:
    sf::Text text;
};


#endif //CATGAME_TEXTCONTAINER_H
