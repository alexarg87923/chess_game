#ifndef HITBOX_H
#define HITBOX_H

#include "SFML/Graphics/RectangleShape.hpp"

#include <map>

#include "types.hpp"

class Piece;

class Hitbox {
public:
    Hitbox(sf::Vector2f incoming_size, const Position& incoming_pos, sf::Vector2f incoming_position, sf::Color incoming_color, Piece* incoming_parent);
    ~Hitbox();

    Piece* get_parent() const;
    sf::RectangleShape get_hitbox() const;
    Position get_position() const;

    bool operator==(const Hitbox& other) const;
    bool operator==(const Hitbox* other) const;
private:
    Piece* parent;
    sf::RectangleShape hitbox;
    Position position;
};

#endif
