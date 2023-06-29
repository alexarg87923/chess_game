#include "pieces/knight.hpp"

Knight::Knight(){}
Knight::~Knight(){}
Knight::Knight(Position pos, char team_color) : Knight(pos.first, pos.second, team_color) {}
Knight::Knight(char row, int col, char team_color) : Piece(row, col, team_color) {
    piece->setTexture(load_sprite(name, team_color));
    calc_valid_moves();
    save_piece_to_map(team, name, this);
}

void Knight::calc_valid_moves() {
    Piece::calc_valid_moves();
    
    if (name != "king" && is_king_in_check()) return;

    std::pair<int, int> offsets[] = {{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

    for (const auto& offset : offsets) {
        int newX = position.first + offset.first;
        int newY = position.second + offset.second;

        if (!validate_move(newX, newY)) continue;

        valid_moves.emplace_back(newX, newY);
    }

    save_moves_globally(name);
}