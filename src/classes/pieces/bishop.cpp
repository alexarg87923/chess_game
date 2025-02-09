#include "pieces/bishop.hpp"

Bishop::Bishop(){}
Bishop::~Bishop(){}

Bishop::Bishop(const Position& pos, Color team_color, sf::Vector2f size) : Bishop(pos.row, pos.col, team_color, size) {}
Bishop::Bishop(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, "bishop", size) {}

std::map<MoveAttributes, std::vector<std::queue<Position>>> Bishop::calc_moves(const Position& pos) const {
    char row_start = pos.row, row_end = 7 + 'A';
    int col_start = pos.col, col_end = BOARD_COL;

    int j = col_start + 1; 

    std::map<MoveAttributes, std::vector<std::queue<Position>>> moves;

    moves[MoveAttributes::OBSTRUCT_ON_OCCUPY].emplace_back();
    for (char i = row_start - 1, j = col_start + 1; i >= row_start && j <= BOARD_COL; i--, j++) {
        moves[MoveAttributes::OBSTRUCT_ON_OCCUPY].back().push({i, j});
    }

    moves[MoveAttributes::OBSTRUCT_ON_OCCUPY].emplace_back();
    for (char i = row_start + 1, j = col_start + 1; i <= row_end && j <= BOARD_COL; i++, j++) {
        moves[MoveAttributes::OBSTRUCT_ON_OCCUPY].back().push({i, j});
    }

    moves[MoveAttributes::OBSTRUCT_ON_OCCUPY].emplace_back();
    for (char i = row_start + 1, j = col_start - 1; i <= row_end && j >= col_start; i++, j--) {
        moves[MoveAttributes::OBSTRUCT_ON_OCCUPY].back().push({i, j});
    }

    moves[MoveAttributes::OBSTRUCT_ON_OCCUPY].emplace_back();
    for (char i = row_start - 1, j = col_start - 1; i >= row_start && j >= col_start; i--, j--) {
        moves[MoveAttributes::OBSTRUCT_ON_OCCUPY].back().push({i, j});
    }


    return moves;
}