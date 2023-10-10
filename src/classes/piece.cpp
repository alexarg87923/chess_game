#include "piece.hpp"

// #include "hitbox.hpp"

Piece::Piece(){}
Piece::~Piece(){}

Piece::Piece(char row, int col, Color team_color, const PIECE& piece, sf::Vector2f size, const std::string& name) :
    Piece(Position{row, col}, team_color, piece, size, name)
{}

Piece::Piece(const Position& pos, Color team_color, const PIECE& piece, sf::Vector2f size, const std::string& name) {
    piece_rect_obj = std::make_unique<sf::RectangleShape>(size);
    piece_rect_obj->setTexture(load_sprite(name, team_color));

    piece_type = piece;
    team = team_color;
    piece_position = pos;
}

bool Piece::operator==(const Piece& other) const {
    // Comparing Color enum values directly
    if (team != other.team) return false;

    // Comparing the names
    if (piece_type != other.piece_type) return false;

    // Comparing Position objects
    if (piece_position != other.piece_position) return false;

    // All checks passed, the objects are equal
    return true;
}

void Piece::draw(sf::RenderTarget& target) const {
    target.draw(*piece_rect_obj);
}

PIECE Piece::get_piece_type() {
    return piece_type;
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


bool Piece::validate_in_bounds(char row, int col) const {
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

bool Piece::is_king() const {
    return (piece_type == PIECE::King);
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

void Piece::invalidate_moves() {
    are_moves_valid = false;
}

const std::vector<std::queue<std::shared_ptr<Hitbox>>>& Piece::get_moves() const {
    return cached_moves;
}

std::vector<std::queue<std::shared_ptr<Hitbox>>>& Piece::get_moves_mutable() {
    return cached_moves;
}

void Piece::cache_moves(const std::vector<std::queue<std::shared_ptr<Hitbox>>>& moves) {
    cached_moves = moves;
    are_moves_valid = true;
}

bool Piece::moves_are_valid() const {
    return are_moves_valid;
}


/*
    OVERLOADED FUNCTIONS
*/

bool Piece::validate_in_bounds(const Position &pos) const {
    return validate_in_bounds(pos.row, pos.col);
}