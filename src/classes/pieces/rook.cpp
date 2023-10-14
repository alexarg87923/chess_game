#include "pieces/rook.hpp"

Rook::Rook(){}
Rook::~Rook(){}

Rook::Rook(const Position& pos, Color team_color, sf::Vector2f size) : Rook(pos.row, pos.col, team_color, size) {}
Rook::Rook(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, PIECE::Rook, size, "rook") {}

    std::vector<std::queue<std::shared_ptr<Hitbox>>> Rook::calc_moves(const Position& pos) {
    char row_current = pos.row, row_end = 7 + 'A';
    int col_current = pos.col, col_end = BOARD_COL;

    std::vector<std::queue<std::shared_ptr<Hitbox>>> moves;

    std::shared_ptr<Rook> self = std::dynamic_pointer_cast<Rook>(shared_from_this());
    std::weak_ptr<Piece> weak_self = self;

    // LEFT
    std::queue<std::shared_ptr<Hitbox>> leftMoves;
    for (char i = row_current - 1; i >= 'A'; i--) {
        Position pos{static_cast<char>(i), col_current};
        leftMoves.push(std::make_shared<Hitbox>(pos, COORDINATES[pos], weak_self));
    }
    moves.push_back(leftMoves);

    // UP
    std::queue<std::shared_ptr<Hitbox>> upMoves;
    for (int i = col_current + 1; i <= col_end; i++) {
        Position pos{row_current, i};
        upMoves.push(std::make_shared<Hitbox>(pos, COORDINATES[pos], weak_self));
    }
    moves.push_back(upMoves);

    // RIGHT
    std::queue<std::shared_ptr<Hitbox>> rightMoves;
    for (char i = row_current + 1; i <= row_end; i++) {
        Position pos{i, col_current};
        rightMoves.push(std::make_shared<Hitbox>(pos, COORDINATES[pos], weak_self));
    }
    moves.push_back(rightMoves);

    // DOWN
    std::queue<std::shared_ptr<Hitbox>> downMoves;
    for (int i = col_current - 1; i >= 1; i--) {
        Position pos{row_current, i};
        downMoves.push(std::make_shared<Hitbox>(pos, COORDINATES[pos], weak_self));
    }
    moves.push_back(downMoves);

    return moves;
}