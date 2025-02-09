#include "pieces/rook.hpp"

Rook::Rook(){}
Rook::~Rook(){}

Rook::Rook(const Position& pos, Color team_color, sf::Vector2f size) : Rook(pos.row, pos.col, team_color, size) {}
Rook::Rook(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, "rook", size) {}

std::map<MoveAttributes, std::vector<std::queue<Position>>> Rook::calc_moves(const Position& pos) const {
    char row_begin = pos.row, row_end = 7 + 'A';
    int col_begin = pos.col, col_end = BOARD_COL;

    int direction = -1;

    std::map<MoveAttributes, std::vector<std::queue<Position>>> moves;

    // LEFT
    row_begin--;
    for (char i = row_begin; i >= 'A'; i--) {
        moves[direction].push({i, pos.col});
    }

    direction--;

    // UP
    col_begin++;
    for (int i = col_begin; i <= col_end; i++) {
        moves[direction].push({pos.row, i});
    }

    direction--;

    row_begin = pos.row;
    col_begin = pos.col;

    // RIGHT
    row_begin++;
    for (char i = row_begin; i <= row_end; i++) {
        moves[direction].push({i, pos.col});
    }

    direction--;
    
    // DOWN
    col_begin--;
    for (int i = col_begin; i >= 1; i--) {
        moves[direction].push({pos.row, i});
    }

    return moves;
}