#include "pieces/pawn.hpp"

enum MovementType {
    STRAIGHT = -100,
    DIAGONAL = -99
};

struct Offset {
    int row;
    int col;
};

const std::vector<Offset> INITIAL_OFFSETS = {
    {0, 0},   // Placholder for straight move
    {0, 0},    // Placeholder for straight move 2 squares
    {1, 1},   // Diagonal right move for WHITE
    {-1, 1},  // Diagonal left move for WHITE
};

Pawn::Pawn(){}
Pawn::~Pawn(){}

Pawn::Pawn(const Position& pos, Color team_color, sf::Vector2f size) : Pawn(pos.row, pos.col, team_color, size) {}
Pawn::Pawn(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, "pawn", size) {}

std::map<MoveAttributes, std::vector<std::queue<Position>>> Pawn::calc_moves(const Position& pos) const {
    std::map<MoveAttributes, std::vector<std::queue<Position>>> moves;
    int direction = (team == WHITE) ? WHITE : BLACK;
    
    auto offsets = INITIAL_OFFSETS;
    for (auto& offset : offsets) {
        offset.col *= direction;
    }

    if (first_move) {
        offsets[0] = {0, direction};
        offsets[1] = {0, 2 * direction};
    }

    for (const auto& offset : offsets) {
        int newX = pos.row + offset.row;
        int newY = pos.col + offset.col;

        if (validate_in_bounds(newX, newY)) {
            if (offset.row != 0) {
                moves[DIAGONAL].push(Position{static_cast<char>(newX), newY});

            } else {
                moves[STRAIGHT].push(Position{static_cast<char>(newX), newY});
            }
        }
    }

    return moves;
}