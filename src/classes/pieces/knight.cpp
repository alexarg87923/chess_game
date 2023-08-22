#include "pieces/knight.hpp"

Knight::Knight(){}
Knight::~Knight(){}
Knight::Knight(const Position& pos, Color team_color, sf::Vector2f size) : Knight(pos.row, pos.col, team_color, size) {}
Knight::Knight(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, "knight", size) {}

std::vector<Position> Knight::get_moves(const Position& pos) const {
    std::pair<int, int> offsets[] = {{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

    std::vector<Position> moves;

    for (const auto& offset : offsets) {
        int newX = piece_position.row + offset.first;
        int newY = piece_position.col + offset.second;

        if (!validate_move(newX, newY)) continue;

        moves.emplace_back(Position{static_cast<char>(newX), newY});
    }
    return moves;
}