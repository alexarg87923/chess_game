#include "pieces/bishop.hpp"

Bishop::Bishop(){}
Bishop::~Bishop(){}

Bishop::Bishop(const Position& pos, Color team_color, sf::Vector2f size) : Bishop(pos.row, pos.col, team_color, size) {}
Bishop::Bishop(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, PIECE::Bishop, size, "bishop") {}

std::vector<std::queue<std::shared_ptr<Hitbox>>> Bishop::calc_moves(const Position& pos) {
    char row_start = pos.row, row_end = 7 + 'A';
    int col_start = pos.col, col_end = BOARD_COL;

    std::vector<std::queue<std::shared_ptr<Hitbox>>> moves;
    // Diagonal up-right
    std::queue<std::shared_ptr<Hitbox>> up_right;
    for (char i = row_start - 1, j = col_start + 1; i >= 'A' && j <= col_end; i--, j++) {
        Position pos{i, j};
        up_right.push(std::make_shared<Hitbox>(pos, COORDINATES[pos], this));
    }
    moves.push_back(up_right);

    // Diagonal down-right
    std::queue<std::shared_ptr<Hitbox>> down_right;
    for (char i = row_start + 1, j = col_start + 1; i <= row_end && j <= col_end; i++, j++) {
        Position pos{i, j};
        down_right.push(std::make_shared<Hitbox>(pos, COORDINATES[pos], this));
    }
    moves.push_back(down_right);

    // Diagonal down-left
    std::queue<std::shared_ptr<Hitbox>> down_left;
    for (char i = row_start + 1, j = col_start - 1; i <= row_end && j >= 1; i++, j--) {
        Position pos{i, j};
        down_left.push(std::make_shared<Hitbox>(pos, COORDINATES[pos], this));
    }
    moves.push_back(down_left);

    // Diagonal up-left
    std::queue<std::shared_ptr<Hitbox>> up_left;
    for (char i = row_start - 1, j = col_start - 1; i >= 'A' && j >= 1; i--, j--) {
        Position pos{i, j};
        up_left.push(std::make_shared<Hitbox>(pos, COORDINATES[pos], this));
    }
    moves.push_back(up_left);

    return moves;
}