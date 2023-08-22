#include "pieces/pawn.hpp"

#include "board.hpp"

Pawn::Pawn() {}
Pawn::~Pawn() {}
Pawn::Pawn(const Position& pos, Color team_color, sf::Vector2f size) : Pawn(pos.row, pos.col, team_color, size) {}
Pawn::Pawn(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, "pawn", size) {}

std::vector<Position> Pawn::get_moves(const Position& pos) const {
    std::vector<Position> moves;
    Position pos_copy = pos;

    int direction = (team == WHITE) ? 1 : -1;

    std::pair<int, int> offsets[4] = {
        {0, direction},
        {1, direction},
        {-1, direction},
        {0, 0} // placeholder
    };

    if (first_move) {
        offsets[0] = {0, 2 * direction};
        offsets[3] = {0, 1 * direction};
    }

    for (const auto& offset : offsets) {
        int newX = pos_copy.row + offset.first;
        int newY = pos_copy.col + offset.second;

        if (validate_move(newX, newY)) {
            if (offset.first == 0) { 
                moves.push_back(Position{static_cast<char>(newX), newY});
            } else {
                moves.push_back(Position{static_cast<char>(newX), newY});
            }
        }
    }

    return moves;
}

void Pawn::update_position(const Position& pos) {
    if (first_move) {
        first_move = false;
    }
    
    Piece::update_position(pos);
}