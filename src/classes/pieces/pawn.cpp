#include "pieces/pawn.hpp"

Pawn::Pawn(){}
Pawn::~Pawn(){}

Pawn::Pawn(const Position& pos, Color team_color, sf::Vector2f size) : Pawn(pos.row, pos.col, team_color, size) {}
Pawn::Pawn(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, "pawn", size) {}

std::map<int, std::queue<Position>> Pawn::calc_moves(const Position& pos) const {
    enum MovementType {
    DIAGONAL = 0,
    STRAIGHT = 1
    };

    const std::pair<int, int> INITIAL_OFFSETS[4] = {
    {0, 1},   // Forward move for WHITE
    {1, 1},   // Diagonal right move for WHITE
    {-1, 1},  // Diagonal left move for WHITE
    {0, 0}    // Placeholder
};

    std::map<int, std::queue<Position>> moves;
    Position pos_copy = pos;

    int direction = (team == WHITE) ? WHITE : BLACK;

    std::pair<int, int> offsets[4];
    std::copy(std::begin(INITIAL_OFFSETS), std::end(INITIAL_OFFSETS), std::begin(offsets));
    for (auto& offset : offsets) {
        offset.second *= direction;
    }

    if (first_move) {
        offsets[0] = {0, 2 * direction};
        offsets[3] = {0, direction};
    }

    for (const auto& offset : offsets) {
        int newX = pos_copy.row + offset.first;
        int newY = pos_copy.col + offset.second;

        if (validate_in_bounds(newX, newY)) {
            if (offset.first != 0) {
                moves[DIAGONAL].push(Position{static_cast<char>(newX), newY});
            } else {
                moves[STRAIGHT].push(Position{static_cast<char>(newX), newY});
            }
        }
    }

    return moves;
}