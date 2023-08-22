#include "pieces/queen.hpp"

Queen::Queen(){}
Queen::~Queen(){}

Queen::Queen(const Position& pos, Color team_color, sf::Vector2f size) : Queen(pos.row, pos.col, team_color, size) {}
Queen::Queen(char row, int col, Color team_color, sf::Vector2f size) : Piece(row, col, team_color, "queen", size) {}

std::map<MoveAttributes, std::vector<std::queue<Position>>> Queen::calc_moves(const Position& pos) const {
    auto bishop_moves = Bishop::calc_moves(pos);
    auto rook_moves = Rook::calc_moves(pos);
    
    std::map<MoveAttributes, std::vector<std::queue<Position>>> combined_moves;

    for (const auto& [move_attr, vec_positions] : bishop_moves) {
        combined_moves[move_attr].insert(
            combined_moves[move_attr].end(), 
            vec_positions.begin(), 
            vec_positions.end()
        );
    }

    for (const auto& [move_attr, vec_positions] : rook_moves) {
        combined_moves[move_attr].insert(
            combined_moves[move_attr].end(), 
            vec_positions.begin(), 
            vec_positions.end()
        );
    }

    return combined_moves;
}