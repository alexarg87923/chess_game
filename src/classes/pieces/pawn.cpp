#include "pieces/pawn.hpp"

Pawn::Pawn() {}
Pawn::~Pawn() {}
Pawn::Pawn(Position pos, char team_color) : Pawn(pos.first, pos.second, team_color) {}
Pawn::Pawn(char row, int col, char team_color) : Piece(row, col, team_color) {
    piece->setTexture(load_sprite(name, team_color));
    calc_valid_moves();
    save_piece_to_map(team, name, this);
}



void Pawn::calc_valid_moves() {
    Piece::calc_valid_moves();

    if (name != "king" && is_king_in_check()) return;

    valid_moves = get_moves(piece_position);
}

std::vector<Position> Pawn::get_moves(Position pos, bool get_every_move) {
    std::vector<Position> moves;

    int direction = (team == 'w') ? 1 : -1;

    std::pair<int, int> offsets[] = {{0, direction}, {1, direction}, {-1, direction}};
    
    if (first_move) {
        offsets[0] = {0, 2 * direction};
    }

    for (const auto& offset : offsets) {
        int newX = pos.first + offset.first;
        int newY = pos.second + offset.second;
        
        // add conditions to push the moves only if the move is valid
        // assuming that Board::check_piece(newX, newY) checks if a position is valid or not
        if (offset.first == 0) { 
            // pawn can move forward (directly in front) if no piece is there
            if (!Board::check_piece(newX, newY)) {
                moves.emplace_back(newX, newY);
            }
        } else {
            // pawn can move diagonally forward only if there is a piece to capture
            if (Board::check_piece(newX, newY)) {
                moves.emplace_back(newX, newY);
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