#include "pieces/bishop.hpp"

Bishop::Bishop(){}
Bishop::~Bishop(){}
Bishop::Bishop(Position pos, char team_color) : Bishop(pos.first, pos.second, team_color) {}
Bishop::Bishop(char row, int col, char team_color) : Piece(row, col, team_color) {
    piece->setTexture(load_sprite(name, team_color));
    calc_valid_moves();
    save_piece_to_map(team, name, this);
}


void Bishop::calc_valid_moves() {
    Piece::calc_valid_moves();

    if (name != "king" && is_king_in_check()) return;

    valid_moves = get_moves(piece_position);
}

std::vector<Position> Bishop::get_moves(Position pos, bool get_every_move) {
    char row_begin = pos.first, row_end = 7 + 'A';
    int col_begin = pos.second, col_end = BOARD_COL;

    int j = col_begin + 1;

    std::vector<Position> all_moves;    

    // TOP LEFT
    for (char i = row_begin - 1, j = col_begin + 1; i >= 'A' && j <= BOARD_COL; i--, j++) {
        all_moves.push_back(std::make_pair(i, j));
        if (Board::check_piece(i, j) && !get_every_move) break;
    }

    // TOP RIGHT
    for (char i = row_begin + 1, j = col_begin + 1; i <= 'H' && j <= BOARD_COL; i++, j++) {
        all_moves.push_back(std::make_pair(i, j));
        if (Board::check_piece(i, j) && !get_every_move) break;
    }

    // BOTTOM RIGHT
    for (char i = row_begin + 1, j = col_begin - 1; i <= 'H' && j > 0; i++, j--) {
        all_moves.push_back(std::make_pair(i, j));
        if (Board::check_piece(i, j) && !get_every_move) break;
    }

    // BOTTOM LEFT
    for (char i = row_begin - 1, j = col_begin - 1; i >= 'A' && j > 0; i--, j--) {
        all_moves.push_back(std::make_pair(i, j));
        if (Board::check_piece(i, j) && !get_every_move) break;
    }

    return all_moves;
}
