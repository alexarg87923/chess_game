#include "pieces/king.hpp"

King::King(){}
King::~King(){}

King::King(const Position& pos, Color team_color, sf::Vector2f size) : King(pos.row, pos.col, team_color, size) {}
King::King(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, "king", size) {}

std::map<MoveAttributes, std::vector<std::queue<Position>>> King::calc_moves(const Position& pos) const {
    const int RANGE_START = -1;
    const int RANGE_END = 2;
    const int ZERO_OFFSET = 0;

    std::map<MoveAttributes, std::vector<std::queue<Position>>> moves;
    moves[MoveAttributes::SEARCH].emplace_back();
    Position pos_copy = pos;
    int direction = 0;
    
    for (int i = RANGE_START; i < RANGE_END; i++) {
        for (int j = RANGE_START; j < RANGE_END; j++) {
            Position new_pos = {static_cast<char>(pos_copy.row + i), pos_copy.col + j};
            if (!(i == ZERO_OFFSET && j == ZERO_OFFSET)) {
                if (validate_in_bounds(new_pos)) {
                    std::queue<Position> tmp;
                    tmp.push(new_pos);
                    moves[MoveAttributes::SEARCH].push_back(tmp);
                }
            }
        }
    } 

    return moves;
}
