#include "pieces/pawn.hpp"

#include "board.hpp"

Pawn::Pawn() {}
Pawn::~Pawn() {}
Pawn::Pawn(Position pos, char team_color) : Pawn(pos.first, pos.second, team_color) {}
Pawn::Pawn(char row, int col, char team_color) : Piece(row, col, team_color) {
    piece->setTexture(load_sprite(name, team_color));
    calc_valid_moves();
    save_piece_to_map(team, name, this);
}



void Pawn::calc_valid_moves() {
    valid_moves.clear();

    valid_moves = get_moves(piece_position);

    Piece::calc_valid_moves();
}

std::vector<Position> Pawn::get_moves(Position pos, bool get_every_move) {
    std::vector<Position> moves;

    int direction = (team == 'w') ? 1 : -1;

    std::pair<int, int> offsets[4] = {
        {0, direction},
        {1, direction},
        {-1, direction},
        {0, 0} // placeholder
    };

    if (first_move) {
        offsets[0] = {0, 2 * direction};
        offsets[3] = {0, 1 * direction};
    }

    for (const auto& offset : offsets) {
        int newX = pos.first + offset.first;
        int newY = pos.second + offset.second;

        if (validate_move(newX, newY)) {
            if (offset.first == 0) { 
                if (!Board::check_piece(newX, newY)) {
                    moves.emplace_back(newX, newY);
                }
            } else {
                if (Board::check_piece(newX, newY)) {
                    moves.emplace_back(newX, newY);
                }
            }
        }
    }

    return moves;
}

void Pawn::update_position(Position pos) {
    if (first_move) {
        first_move = false;
    }
    
    Piece::update_position(pos);
}