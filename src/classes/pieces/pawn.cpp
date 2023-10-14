#include "pieces/pawn.hpp"
struct Offset {
    int row;
    int col;
};

// enum MovementType {
//     STRAIGHT,
//     DIAGONAL
// };

std::vector<Offset> INITIAL_OFFSETS = {
    {0, 1},   // Placholder for straight move
    {1, 1},   // Diagonal right move for WHITE
    {-1, 1},  // Diagonal left move for WHITE
};

Pawn::Pawn(){}
Pawn::~Pawn(){}

Pawn::Pawn(const Position& pos, Color team_color, sf::Vector2f size) : Pawn(pos.row, pos.col, team_color, size) {}
Pawn::Pawn(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, PIECE::Pawn, size, "pawn") {}

std::vector<std::queue<std::shared_ptr<Hitbox>>> Pawn::calc_moves(const Position& pos) {
    std::vector<std::queue<std::shared_ptr<Hitbox>>> moves;
    moves.push_back(std::queue<std::shared_ptr<Hitbox>>());

    std::shared_ptr<Pawn> self = std::static_pointer_cast<Pawn>(shared_from_this());
    std::weak_ptr<Piece> weak_self = self;

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
            Position pos{static_cast<char>(newX), newY};
            if (offset.row != 0) {
                std::queue<std::shared_ptr<Hitbox>> q;
                q.push(std::make_shared<Hitbox>(pos, COORDINATES[pos], weak_self));
                moves.push_back(q);
            } else {
                moves[STRAIGHT].push(std::make_shared<Hitbox>(pos, COORDINATES[pos], weak_self));
            }
        }
    }

    return moves;
}