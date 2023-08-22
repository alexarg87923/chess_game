#include "pieces/rook.hpp"

#include "board.hpp"

Rook::Rook(){}
Rook::~Rook(){}
Rook::Rook(Position pos, char team_color) : Rook(pos.first, pos.second, team_color) {}
Rook::Rook(char row, int col, char team_color) : Piece(row, col, team_color) {
    piece->setTexture(load_sprite(name, team_color));
    calc_valid_moves();
    save_piece_to_map(team, name, this);
}

void Rook::calc_valid_moves() {
    valid_moves.clear();

    valid_moves = get_moves(piece_position);

    Piece::calc_valid_moves();
}

std::vector<Position> Rook::get_moves(Position pos, bool get_every_move) {
    char row_begin = pos.first, row_end = 7 + 'A';
    int col_begin = pos.second, col_end = BOARD_COL;

    std::vector<Position> moves;

    // LEFT
    row_begin--;
    for (char i = row_begin; i >= 'A'; i--) {
        moves.push_back(std::make_pair(i, pos.second));
        if (Board::check_piece(i, pos.second) && !get_every_move)
            break;
    }
    // UP
    col_begin++;
    for (int i = col_begin; i <= col_end; i++) {
        moves.push_back(std::make_pair(pos.first, i));
        if (Board::check_piece(pos.first, i) && !get_every_move)
            break;
    }

    row_begin = pos.first;
    col_begin = pos.second;

    // RIGHT
    row_begin++;
    for (char i = row_begin; i <= row_end; i++) {
        moves.push_back(std::make_pair(i, pos.second));
        if (Board::check_piece(i, pos.second) && !get_every_move)
            break;
    }
    
    // DOWN
    col_begin--;
    for (int i = col_begin; i >= 1; i--) {
        moves.push_back(std::make_pair(pos.first, i));
        if (Board::check_piece(pos.first, i) && !get_every_move)
            break;
    }

    return moves;
}