#include "pieces/pawn.hpp"
struct Offset {
    int row;
    int col;
};

enum MovementType {
    STRAIGHT,
    DIAGONAL
};

std::vector<Offset> INITIAL_OFFSETS = {
    {0, 1},   // Placholder for straight move
    {1, 1},   // Diagonal right move for WHITE
    {-1, 1},  // Diagonal left move for WHITE
};

Pawn::Pawn(){}
Pawn::~Pawn(){}

Pawn::Pawn(const Position& pos, Color team_color, sf::Vector2f size) : Pawn(pos.row, pos.col, team_color, size) {}
Pawn::Pawn(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, "pawn", size) {}

std::map<MoveAttributes, std::vector<std::queue<Position>>> Pawn::calc_moves(const Position& pos) const {
    std::map<MoveAttributes, std::vector<std::queue<Position>>> moves;
    moves[MoveAttributes::OBSTRUCT_ON_OCCUPY].push_back(std::queue<Position>());

    int direction = (team == WHITE) ? 1 : -1; // Assuming WHITE should move in the positive direction and BLACK in the negative

    auto offsets = INITIAL_OFFSETS;

    for (auto& offset : offsets) {
        offset.col *= direction;
    }

    if (first_move) {
        offsets.push_back({0, 2 * direction});
    }

    for (auto& offset : offsets) {
        int newX = pos.row + offset.row;
        int newY = pos.col + offset.col;
        if (validate_in_bounds(newX, newY)) {

            if (offset.row != 0) {
                std::queue<Position> q;
                q.push(Position{static_cast<char>(newX), newY});

                moves[MoveAttributes::VALID_ON_ENEMY_ONLY].push_back(q);
            } else {
                moves[MoveAttributes::OBSTRUCT_ON_OCCUPY][STRAIGHT].push(Position{static_cast<char>(newX), newY});
            }
        }
    }

    return moves;
}