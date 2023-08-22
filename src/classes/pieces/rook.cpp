#include "pieces/rook.hpp"

Rook::Rook(){}
Rook::~Rook(){}

Rook::Rook(const Position& pos, Color team_color, sf::Vector2f size) : Rook(pos.row, pos.col, team_color, size) {}
Rook::Rook(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, "rook", size) {}

std::map<MoveAttributes, std::vector<std::queue<Position>>> Rook::calc_moves(const Position& pos) const {
    char row_current = pos.row, row_end = 7 + 'A';
    int col_current = pos.col, col_end = BOARD_COL;

    std::map<MoveAttributes, std::vector<std::queue<Position>>> moves;

    // LEFT
    std::queue<Position> leftMoves;
    for (char i = row_current - 1; i >= 'A'; i--) {
        leftMoves.push({i, col_current});
    }
    moves[MoveAttributes::SEARCH].push_back(leftMoves);

    // UP
    std::queue<Position> upMoves;
    for (int i = col_current + 1; i <= col_end; i++) {
        upMoves.push({row_current, i});
    }
    moves[MoveAttributes::SEARCH].push_back(upMoves);

    // RIGHT
    std::queue<Position> rightMoves;
    for (char i = row_current + 1; i <= row_end; i++) {
        rightMoves.push({i, col_current});
    }
    moves[MoveAttributes::SEARCH].push_back(rightMoves);

    // DOWN
    std::queue<Position> downMoves;
    for (int i = col_current - 1; i >= 1; i--) {
        downMoves.push({row_current, i});
    }
    moves[MoveAttributes::SEARCH].push_back(downMoves);

    return moves;
}