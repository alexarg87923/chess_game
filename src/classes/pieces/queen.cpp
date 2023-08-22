#include "pieces/queen.hpp"

Queen::Queen(const Position& pos, Color team_color, sf::Vector2f size, Move_Handler& handler) : Queen(pos.row, pos.col, team_color, size, handler) {}
Queen::Queen(char row, int col, Color team_color, sf::Vector2f size, Move_Handler& handler) : Piece(row, col, team_color, "queen", size, handler),
  Rook(row, col, team_color, size, handler),
  Bishop(row, col, team_color, size, handler) 
{
    valid_moves = get_moves(piece_position);
}

std::vector<Position> Queen::get_moves(const Position& pos, bool get_every_move) const {
    std::vector<Position> moves;

    auto bishop_moves = Bishop::get_moves(pos, get_every_move);
    auto rook_moves = Rook::get_moves(pos, get_every_move);

    moves.reserve(moves.size() + bishop_moves.size() + rook_moves.size());
    moves.insert(moves.end(), bishop_moves.begin(), bishop_moves.end());
    moves.insert(moves.end(), rook_moves.begin(), rook_moves.end());

    return moves;
    return {};
}