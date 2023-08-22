#include "pieces/queen.hpp"

#include "board.hpp"

Queen::Queen(){}
Queen::~Queen(){}
Queen::Queen(Position pos, char team_color) : Queen(pos.first, pos.second, team_color) {}
Queen::Queen(char row, int col, char team_color) : Piece(row, col, team_color) {
    piece->setTexture(load_sprite(name, team_color));
    calc_valid_moves();
    save_piece_to_map(team, name, this);
}


void Queen::calc_valid_moves() {
    Piece::calc_valid_moves();

    if (name != "king" && is_king_in_check()) return;

    valid_moves = Queen::get_moves(piece_position);
}

std::vector<Position> Queen::get_moves(Position pos, bool get_every_move) {
    std::vector<Position> moves;

    auto bishop_moves = Bishop::get_moves(pos, get_every_move);
    auto rook_moves = Rook::get_moves(pos, get_every_move);

    moves.reserve(moves.size() + bishop_moves.size() + rook_moves.size());
    moves.insert(moves.end(), bishop_moves.begin(), bishop_moves.end());
    moves.insert(moves.end(), rook_moves.begin(), rook_moves.end());

    return moves;
}