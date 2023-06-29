#include "pieces/rook.hpp"

Rook::Rook(){}
Rook::~Rook(){}
Rook::Rook(Position pos, char team_color) : Rook(pos.first, pos.second, team_color) {}
Rook::Rook(char row, int col, char team_color) : Piece(row, col, team_color) {
    piece->setTexture(load_sprite(name, team_color));
    calc_valid_moves();
    save_piece_to_map(team, name, this);
}

void Rook::calc_valid_moves() {
    Piece::calc_valid_moves();

    if (name != "king" && is_king_in_check()) return;

    calculate_rook_path(position);
    save_moves_globally(name);
}

void Rook::calculate_rook_path(Position pos) {
    char row_begin = pos.first, row_end = 7 + 'A';
    int col_begin = pos.second, col_end = BOARD_COL;

    // LEFT
    row_begin--;
    for (char i = row_begin; i >= 'A'; i--) {
        valid_moves.push_back(std::make_pair(i, position.second));
        if (Board::check_piece(i, position.second))
            break;
    }
    // UP
    col_begin++;
    for (int i = col_begin; i <= col_end; i++) {
        valid_moves.push_back(std::make_pair(position.first, i));
        if (Board::check_piece(position.first, i))
            break;
    }

    row_begin = position.first;
    col_begin = position.second;

    // RIGHT
    row_begin++;
    for (char i = row_begin; i <= row_end; i++) {
        valid_moves.push_back(std::make_pair(i, position.second));
        if (Board::check_piece(i, position.second))
            break;
    }
    
    // DOWN
    col_begin--;
    for (int i = col_begin; i >= 1; i--) {
        valid_moves.push_back(std::make_pair(position.first, i));
        if (Board::check_piece(position.first, i))
            break;
    }
}