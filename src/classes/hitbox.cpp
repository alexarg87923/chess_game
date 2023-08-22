#include "hitbox.hpp"

#include "piece.hpp"

Hitbox::Hitbox(sf::Vector2f incoming_size, const Position& incoming_pos, sf::Vector2f incoming_position, sf::Color incoming_color, Piece* incoming_parent){
    parent = incoming_parent;
    position = incoming_pos;
    hitbox = sf::RectangleShape(incoming_size);

    hitbox.setFillColor(incoming_color);
    hitbox.setPosition(incoming_position);
}

Hitbox::~Hitbox(){}

Piece* Hitbox::get_parent() const {
    return parent;
}
sf::RectangleShape Hitbox::get_hitbox() const {
    return hitbox;
}
Position Hitbox::get_position() const {
    return position;
}

bool Hitbox::operator==(const Hitbox& other) const {
    return position == other.position && parent == other.parent;
}

bool Hitbox::operator==(const Hitbox* other) const {
    return position == other->position && parent == other->parent;
}

/*
    OVERLOADED FUNCTIONS
*/
