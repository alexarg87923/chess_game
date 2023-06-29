#include "pieces/pawn.hpp"

Pawn::Pawn() {}
Pawn::~Pawn() {}
Pawn::Pawn(Position pos, char team_color) : Pawn(pos.first, pos.second, team_color) {}
Pawn::Pawn(char row, int col, char team_color) : Piece(row, col, team_color) {
    piece->setTexture(load_sprite(name, team_color));
    calc_valid_moves();
    save_piece_to_map(team, name, this);
}



void Pawn::calc_valid_moves() {
    Piece::calc_valid_moves();

    if (name != "king" && is_king_in_check()) return;

    auto pos = get_pos();

    int direction = (team == 'w') ? 1 : -1;

    if (first_move) {
        valid_moves.push_back(std::make_pair(pos.first, pos.second + (2 * direction)));
        valid_moves.push_back(std::make_pair(pos.first, pos.second + direction));
    } else {
        valid_moves.push_back(std::make_pair(pos.first, pos.second + direction));
    }

    if (Board::check_piece(pos.first + 1, pos.second + direction)) {
        valid_moves.push_back(std::make_pair(pos.first + 1, pos.second + direction));
    }
    if (Board::check_piece(pos.first - 1, pos.second + direction)) {
        valid_moves.push_back(std::make_pair(pos.first - 1, pos.second + direction));
    }

    save_moves_globally(name);
}

void Pawn::update_position(Position pos) {
    if (first_move) {
        first_move = false;
    }
    Piece::update_position(pos);
}