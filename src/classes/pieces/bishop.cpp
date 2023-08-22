#include "pieces/bishop.hpp"

#include "board.hpp"

Bishop::Bishop(){}
Bishop::~Bishop(){}
Bishop::Bishop(const Position& pos, Color team_color, sf::Vector2f size) : Bishop(pos.row, pos.col, team_color, size) {}
Bishop::Bishop(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, "bishop", size) {}

std::vector<Position> Bishop::get_moves(const Position& pos) const {
    char row_begin = pos.row, row_end = 7 + 'A';
    int col_begin = pos.col, col_end = BOARD_COL;

    int j = col_begin + 1;

    std::vector<Position> all_moves;    

    // TOP LEFT
    for (char i = row_begin - 1, j = col_begin + 1; i >= 'A' && j <= BOARD_COL; i--, j++) {
        all_moves.push_back({i, j});
    }

    // TOP RIGHT
    for (char i = row_begin + 1, j = col_begin + 1; i <= 'H' && j <= BOARD_COL; i++, j++) {
        all_moves.push_back({i, j});
    }

    // BOTTOM RIGHT
    for (char i = row_begin + 1, j = col_begin - 1; i <= 'H' && j > 0; i++, j--) {
        all_moves.push_back({i, j});
    }

    // BOTTOM LEFT
    for (char i = row_begin - 1, j = col_begin - 1; i >= 'A' && j > 0; i--, j--) {
        all_moves.push_back({i, j});
    }

    return all_moves;
}
