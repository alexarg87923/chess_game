#ifndef HITBOX_H
#define HITBOX_H

#include "SFML/Graphics/RectangleShape.hpp"

#include <map>

#include "types.hpp"

class Piece;

class Hitbox {
public:
    Hitbox(sf::Vector2f incoming_size, const Position& incoming_pos, sf::Vector2f incoming_position, std::shared_ptr<Piece> incoming_parent);

    std::shared_ptr<Piece> get_parent() const;
    sf::RectangleShape* get_hitbox() const;
    Position get_position() const;

    bool operator==(const std::shared_ptr<Hitbox>& other) const;

private:
    std::shared_ptr<Piece> parent;
    std::unique_ptr<sf::RectangleShape> hitbox;
    Position position;
    bool showing = false;
};

#endif
