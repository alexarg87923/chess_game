#include "pieces/queen.hpp"

Queen::Queen(){}
Queen::~Queen(){}
Queen::Queen(const Position& pos, Color team_color, sf::Vector2f size) : Queen(pos.row, pos.col, team_color, size) {}
Queen::Queen(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, "queen", size) {}

std::vector<Position> Queen::get_moves(const Position& pos) const {
    std::vector<Position> moves;

    auto bishop_moves = Bishop::get_moves(pos);
    auto rook_moves = Rook::get_moves(pos);

    moves.reserve(moves.size() + bishop_moves.size() + rook_moves.size());
    moves.insert(moves.end(), bishop_moves.begin(), bishop_moves.end());
    moves.insert(moves.end(), rook_moves.begin(), rook_moves.end());

    return moves;
    return {};
}