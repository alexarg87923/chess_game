#include "piece.hpp"
#include "board.hpp"
#include "pieces/king.hpp"

Piece::Piece(char row, int col, char team_color) : Piece(std::make_pair(row, col), team_color) {}
Piece::Piece(Position pos, char team_color) {
    team = team_color;
    save_piece(new sf::RectangleShape(Board::get_size_of_grid_square()));
    set_position(pos);
}

void Piece::save_piece_to_map(char team, std::string name, Piece* piece) {
    Board::save_map_of_pieces(team, name, piece);
}

void Piece::draw(sf::RenderTarget& target) const {
    target.draw(*piece);
}

std::vector<Position> Piece::get_valid_moves() {
    return valid_moves;
}

void Piece::save_piece(sf::RectangleShape *tmp) {
    piece = tmp;
}

Position Piece::get_pos() {
    return position;
}

sf::RectangleShape *Piece::get_ppiece() {
    return piece;
}

void Piece::update_position(Position pos) {
    set_position(pos);

    // Watch for this
    Board::clear_check_hitbox();
    Board::refresh_check_hitbox();
}

void Piece::set_position(Position &pos) {
    Board::update_check_piece(position, false);
    Board::set_piece(position, nullptr);

    position = pos;
    Board::set_piece(position, this);
    Board::update_check_piece(position, true);
    piece->setPosition(Board::pair_to_pos(position));
}

bool Piece::validate_move(char row, int col) {
    // If position is out of bounds, return false, else true
    if (row > 'H' || row < 'A' || col > 8 || col < 1) {
        return false;
    } else {
        return true;
    }
}

std::string Piece::get_working_dir() {
    char buffer[FILENAME_MAX];
    if (getcwd(buffer, sizeof(buffer)) != nullptr) {
        //std::cout << "Current working directory: " << buffer << std::endl;
        return std::string(buffer);
    } else {
        std::cerr << "Failed to get the current working directory." << std::endl;
        return "";
    }
}

sf::Texture* Piece::load_sprite(const std::string& name, char team_color) {
    sf::Texture* sprite = new sf::Texture();
    sprite->loadFromFile(get_working_dir() + "/src/assets/images/" + name + '_' + std::string(1, team_color) + ".png");
    return sprite;
}

void Piece::save_moves_globally(std::string piece_name) {
    Board::save_piece_hitboxes(team, piece_name, valid_moves);
}

bool Piece::is_king_in_check() {
    King* king = dynamic_cast<King*>(Board::get_piece_from_map(team, "king"));
    if(king != nullptr) {
        return king->is_in_check();
    }
    return false;
}

void Piece::calc_valid_moves() {
    valid_moves.clear();
}

/*
    OVERLOADED FUNCTIONS
*/

bool Piece::validate_move(Position pos) {
    return validate_move(pos.first, pos.second);
}