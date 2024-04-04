#include "pieces/knight.hpp"

Knight::Knight(){}
Knight::~Knight(){}

Knight::Knight(const Position& pos, Color team_color, sf::Vector2f size) : Knight(pos.row, pos.col, team_color, size) {}
Knight::Knight(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, PIECE::Knight, size, "knight") {}

std::vector<std::queue<std::shared_ptr<Hitbox>>> Knight::calc_moves(const Position& pos) {
    std::pair<int, int> offsets[] = {{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

    std::shared_ptr<Knight> self = std::static_pointer_cast<Knight>(shared_from_this());
    // std::weak_ptr<Piece> weak_self = self;

    std::vector<std::queue<std::shared_ptr<Hitbox>>> moves;
    moves.emplace_back();
    int direction = 0;

    for (const auto& offset : offsets) {
        int newX = piece_position.row + offset.first;
        int newY = piece_position.col + offset.second;

        std::queue<std::shared_ptr<Hitbox>> tmp;

        if (!validate_in_bounds(newX, newY))
            continue;

        Position pos{static_cast<char>(newX), newY};
        tmp.push(std::make_shared<Hitbox>(pos, COORDINATES[pos], self));

        moves.push_back(tmp);
    }
    return moves;
}