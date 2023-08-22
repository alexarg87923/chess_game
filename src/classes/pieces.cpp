#include "piece.hpp"

#include "hitbox.hpp"

Piece::Piece(Move_Handler& handler) :
    move_handler(handler)
{}

Piece::Piece(char row, int col, Color team_color, const std::string& name, sf::Vector2f size, Move_Handler& handler) :
    Piece(Position{row, col}, team_color, name, size, handler)
{}

Piece::Piece(const Position& pos, Color team_color, const std::string& name, sf::Vector2f size, Move_Handler& handler) :
    move_handler(handler) 
{
    piece_rect_obj = std::make_unique<sf::RectangleShape>(size);
    piece_rect_obj->setTexture(load_sprite(name, team_color));

    piece_name = name;

    team = team_color;

    piece_position = pos;
}

bool Piece::operator==(const Piece& other) const {
    // Comparing Color enum values directly
    if (team != other.team) return false;

    // Comparing the names
    if (piece_name != other.piece_name) return false;

    // Comparing Position objects
    if (piece_position != other.piece_position) return false;

    // All checks passed, the objects are equal
    return true;
}

void Piece::draw(sf::RenderTarget& target) const {
    target.draw(*piece_rect_obj);
}

std::vector<Position> Piece::get_valid_moves() const {
    return valid_moves;
}

void Piece::set_valid_moves(std::vector<Position> incoming_valid_moves) {
    valid_moves = incoming_valid_moves;
}

void Piece::clear_valid_moves() {
    valid_moves.clear();
}

Position Piece::get_pos() const {
    return piece_position;
}

sf::RectangleShape* Piece::get_piece() const {
    return piece_rect_obj.get();
}

void Piece::set_position(sf::Vector2f pos) {
    piece_rect_obj->setPosition(pos);
}

void Piece::set_piece_pos(Position pos) {
    piece_position = pos;
}


bool Piece::validate_move(char row, int col) const {
    // If position is out of bounds, return false, else true
    if (row > 'H' || row < 'A' || col > 8 || col < 1) {
        return false;
    } else {
        return true;
    }
}

sf::Texture* Piece::load_sprite(const std::string& name, Color team_color) const {
    sf::Texture* sprite = new sf::Texture();
    sprite->loadFromFile(get_working_dir() + "/src/assets/images/" + name + '_' + std::to_string(static_cast<int>(team_color)) + ".png");
    return sprite;
}

Color Piece::get_team() const {
    return team;
}

std::vector<std::shared_ptr<Hitbox>> Piece::get_hitboxes() const {
    return hitboxes;
}

void Piece::clear_hitboxes() {
    hitboxes.clear();
}

void Piece::add_hitbox(std::shared_ptr<Hitbox> hitbox) {
    hitboxes.push_back(hitbox);
}

void Piece::add_valid_move(Position pos) {
    valid_moves.push_back(pos);
}


/*
    OVERLOADED FUNCTIONS
*/

bool Piece::validate_move(const Position &pos) const {
    return validate_move(pos.row, pos.col);
}