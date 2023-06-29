#include "pieces/queen.hpp"

Queen::Queen(){}
Queen::~Queen(){}
Queen::Queen(Position pos, char team_color) : Queen(pos.first, pos.second, team_color) {}
Queen::Queen(char row, int col, char team_color) : Piece(row, col, team_color) {
    piece->setTexture(load_sprite(name, team_color));
    calc_valid_moves();
    save_piece_to_map(team, name, this);
}


void Queen::calc_valid_moves() {
    Piece::calc_valid_moves();

    if (name != "king" && is_king_in_check()) return;

    calculate_rook_path(position);
    calculate_bishop_path(position);

    save_moves_globally(name);
}