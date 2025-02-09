#include "pieces/knight.hpp"

Knight::Knight(){}
Knight::~Knight(){}

Knight::Knight(const Position& pos, Color team_color, sf::Vector2f size) : Knight(pos.row, pos.col, team_color, size) {}
Knight::Knight(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, "knight", size) {}

std::map<MoveAttributes, std::vector<std::queue<Position>>> Knight::calc_moves(const Position& pos) const {
    std::pair<int, int> offsets[] = {{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

    std::map<MoveAttributes, std::vector<std::queue<Position>>> moves;
    int direction = 0;

    for (const auto& offset : offsets) {
        int newX = piece_position.row + offset.first;
        int newY = piece_position.col + offset.second;

        if (!validate_in_bounds(newX, newY)) 
            continue;

        moves[direction++].push(Position{static_cast<char>(newX), newY});
    }
    return moves;
}