#include "pieces/queen.hpp"

Queen::Queen(){}
Queen::~Queen(){}

Queen::Queen(const Position& pos, Color team_color, sf::Vector2f size) : Queen(pos.row, pos.col, team_color, size) {}
Queen::Queen(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, PIECE::Queen, size, "queen") {}

std::vector<std::queue<std::shared_ptr<Hitbox>>> Queen::calc_moves(const Position& pos) {
    std::vector<std::queue<std::shared_ptr<Hitbox>>> bishop_moves = Bishop::calc_moves(pos);
    std::vector<std::queue<std::shared_ptr<Hitbox>>> rook_moves = Rook::calc_moves(pos);
    bishop_moves.insert(bishop_moves.end(), rook_moves.begin(), rook_moves.end());
    return bishop_moves;
}