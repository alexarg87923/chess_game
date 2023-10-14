#include "hitbox.hpp"

#include "piece.hpp"

Hitbox::Hitbox(const Position& incoming_pos, sf::Vector2f incoming_position, std::weak_ptr<Piece> incoming_parent){
    parent = incoming_parent;
    position = incoming_pos;

    hitbox = std::make_unique<sf::RectangleShape>();
    hitbox->setSize(sf::Vector2f(0, 0));
    hitbox->setFillColor(sf::Color::Blue);
    hitbox->setPosition(incoming_position);
}

void Hitbox::hide() {
    hitbox->setSize(sf::Vector2f(0, 0));
}

void Hitbox::show() {
    hitbox->setSize(SIZE);
}

void Hitbox::highlight() {
    hitbox->setFillColor(sf::Color(0, 0, 255, 128));
}

std::weak_ptr<Piece> Hitbox::get_parent() const {
    return parent;
}

sf::RectangleShape* Hitbox::get_hitbox() const {
    return hitbox.get();
}

Position Hitbox::get_position() const {
    return position;
}

bool Hitbox::operator==(const std::shared_ptr<Hitbox>& other) const {
    return position == other->position && parent.lock() == other->parent.lock();
}


/*
    OVERLOADED FUNCTIONS
*/
