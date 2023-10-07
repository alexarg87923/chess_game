#include "hitbox.hpp"

#include "piece.hpp"

Hitbox::Hitbox(sf::Vector2f incoming_size, const Position& incoming_pos, sf::Vector2f incoming_position, std::shared_ptr<Piece> incoming_parent){
    parent = incoming_parent;
    position = incoming_pos;

    // hitbox = new sf::RectangleShape();
    hitbox = std::make_unique<sf::RectangleShape>();
    hitbox->setSize(incoming_size);
    hitbox->setFillColor(sf::Color::Transparent);
    hitbox->setPosition(incoming_position);
}

void Hitbox::show() {
    hitbox->setFillColor(sf::Color::Blue);
}

void Hitbox::highlight() {
    hitbox->setFillColor(sf::Color(0, 0, 255, 128));
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
