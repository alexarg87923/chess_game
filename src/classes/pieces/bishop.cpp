#include "pieces/bishop.hpp"

Bishop::Bishop(){}
Bishop::~Bishop(){}

Bishop::Bishop(const Position& pos, Color team_color, sf::Vector2f size) : Bishop(pos.row, pos.col, team_color, size) {}
Bishop::Bishop(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, "bishop", size) {}

std::map<MoveAttributes, std::vector<std::queue<Position>>> Bishop::calc_moves(const Position& pos) const {
    char row_start = pos.row, row_end = 7 + 'A';
    int col_start = pos.col, col_end = BOARD_COL;

    std::map<MoveAttributes, std::vector<std::queue<Position>>> moves;

    // Diagonal up-right
    std::queue<Position> up_right;
    for (char i = row_start - 1, j = col_start + 1; i >= 'A' && j <= col_end; i--, j++) {
        up_right.push({i, j});
    }
    moves[MoveAttributes::SEARCH].push_back(up_right);

    // Diagonal down-right
    std::queue<Position> down_right;
    for (char i = row_start + 1, j = col_start + 1; i <= row_end && j <= col_end; i++, j++) {
        down_right.push({i, j});
    }
    moves[MoveAttributes::SEARCH].push_back(down_right);

    // Diagonal down-left
    std::queue<Position> down_left;
    for (char i = row_start + 1, j = col_start - 1; i <= row_end && j >= 1; i++, j--) {
        down_left.push({i, j});
    }
    moves[MoveAttributes::SEARCH].push_back(down_left);

    // Diagonal up-left
    std::queue<Position> up_left;
    for (char i = row_start - 1, j = col_start - 1; i >= 'A' && j >= 1; i--, j--) {
        up_left.push({i, j});
    }
    moves[MoveAttributes::SEARCH].push_back(up_left);

    return moves;
}