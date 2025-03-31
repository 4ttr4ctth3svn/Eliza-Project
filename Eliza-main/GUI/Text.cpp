#include "Text.hpp"

ELIZA::Text::Text(sf::RenderWindow& win, sf::Font& font) : window(win) {
    _text.setFont(font);
}

void ELIZA::Text::setString(std::string renderString) {
    _text.setString(renderString);
}

std::string ELIZA::Text::getString() {
    return _text.getString();
}

void ELIZA::Text::setStyle(unsigned int style) {
    _text.setStyle(style);
}

void ELIZA::Text::setPosition(float x, float y) {
    _text.setPosition(sf::Vector2f(x, y));
}

void ELIZA::Text::setSize(unsigned int size)  {
    _text.setCharacterSize(size);
}

void ELIZA::Text::setColor(int r, int g, int b) {
    _text.setFillColor(sf::Color(r, g, b));
}

void ELIZA::Text::setColor(sf::Color color) {
    _text.setFillColor(color);
}

// TODO: write implementation for text wrap functionality
void ELIZA::Text::display() {
    window.draw(_text);
}