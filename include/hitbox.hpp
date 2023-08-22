#ifndef HITBOX_H
#define HITBOX_H

#include "SFML/Graphics/RectangleShape.hpp"

#include <map>

#include "types.hpp"

class Piece;

class Hitbox {
public:
    Hitbox(sf::Vector2f iSize, Position iPosPair, sf::Vector2f iPos, sf::Color iColor, Piece* iParent);
    ~Hitbox();

    Piece* get_parent();
    sf::RectangleShape get_hitbox();
    Position get_position();
    
private:
    Piece* parent;
    sf::RectangleShape hitbox;
    Position position;
};

#endif
