#include "hitbox.hpp"

#include "piece.hpp"

Hitbox::Hitbox(sf::Vector2f iSize, Position iPosPair, sf::Vector2f iPos, sf::Color iColor, Piece* iParent){
    parent = iParent;
    position = iPosPair;
    hitbox = sf::RectangleShape(iSize);

    hitbox.setFillColor(iColor);
    hitbox.setPosition(iPos);
}

Hitbox::~Hitbox(){}

Piece* Hitbox::get_parent() {
    return parent;
}
sf::RectangleShape Hitbox::get_hitbox() {
    return hitbox;
}
Position Hitbox::get_position() {
    return position;
}

/*
    OVERLOADED FUNCTIONS
*/
