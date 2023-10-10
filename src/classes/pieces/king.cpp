#include "pieces/king.hpp"

King::King(){}
King::~King(){}

King::King(const Position& pos, Color team_color, sf::Vector2f size) : King(pos.row, pos.col, team_color, size) {}
King::King(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, PIECE::King, size, "king") {}

std::vector<std::queue<std::shared_ptr<Hitbox>>> King::calc_moves(const Position& pos) {
    const int RANGE_START = -1;
    const int RANGE_END = 2;
    const int ZERO_OFFSET = 0;

    std::vector<std::queue<std::shared_ptr<Hitbox>>> moves;
    moves.emplace_back();
    Position pos_copy = pos;
    int direction = 0;
    
    std::queue<std::shared_ptr<Hitbox>> q;

    for (int i = RANGE_START; i < RANGE_END; i++) {
        for (int j = RANGE_START; j < RANGE_END; j++) {
            Position new_pos{static_cast<char>(pos_copy.row + i), pos_copy.col + j};
            if (!(i == ZERO_OFFSET && j == ZERO_OFFSET)) {
                if (validate_in_bounds(new_pos)) {
                    q.push(std::make_shared<Hitbox>(new_pos, COORDINATES[new_pos], this));
                }
            }
        }
    } 

    moves.push_back(q);

    return moves;
}
