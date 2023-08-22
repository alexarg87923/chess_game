#ifndef HITBOX_H
#define HITBOX_H

#include <map>

#include "piece.hpp"
#include "types.hpp"

class Hitbox {
public:
    Hitbox();
    ~Hitbox();

    void set_parent();
    void set_hitbox();
    void set_position();

    Piece* get_parent();
    sf::RectangleShape get_hitbox();
    Position get_position();

private:
    Piece* parent;
    sf::RectangleShape hitbox;
    Position position;
};

#endif
