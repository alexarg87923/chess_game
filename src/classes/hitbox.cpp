#include "hitbox.hpp"

#include "piece.hpp"

Hitbox::Hitbox(sf::Vector2f incoming_size, const Position& incoming_pos, sf::Vector2f incoming_position, std::shared_ptr<Piece> incoming_parent){
    parent = incoming_parent;
    position = incoming_pos;


    hitbox = std::make_unique<sf::RectangleShape>();
    hitbox->setFillColor(sf::Color::Transparent);
    hitbox->setPosition(incoming_position);
}

std::shared_ptr<Piece> Hitbox::get_parent() const {
    return parent;
}

sf::RectangleShape* Hitbox::get_hitbox() const {
    return hitbox.get();
}

Position Hitbox::get_position() const {
    return position;
}

bool Hitbox::operator==(const std::shared_ptr<Hitbox>& other) const {
    return position == other->position && *parent == *other->parent;
}


/*
    OVERLOADED FUNCTIONS
*/
