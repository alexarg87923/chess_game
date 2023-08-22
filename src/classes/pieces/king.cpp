#include "pieces/king.hpp"
#include "window.hpp"

King::King(){}
King::~King(){}
King::King(Position pos, char team_color) : King(pos.first, pos.second, team_color) {}
King::King(char row, int col, char team_color) : Piece(row, col, team_color) {
    piece->setTexture(load_sprite(name, team_color));
    calc_valid_moves();
    save_piece_to_map(team, name, this);
}


void King::calc_valid_moves() {
    Piece::calc_valid_moves();

    if (name != "king" && is_king_in_check()) return;

    valid_moves = get_moves(piece_position);
}

std::vector<Position> King::get_moves(Position pos, bool get_every_move) {
    const int RANGE_START = -1;
    const int RANGE_END = 2;
    const int ZERO_OFFSET = 0;

    std::vector<Position> moves;

    for (int i = RANGE_START; i < RANGE_END; i++) {
        for (int j = RANGE_START; j < RANGE_END; j++) {
            Position new_pos = std::make_pair(pos.first + i, pos.second + j);
            if (!(i == ZERO_OFFSET && j == ZERO_OFFSET)) {
                if (validate_move(new_pos))
                    moves.push_back(new_pos);
            }
        }
    }
    return moves;
}


bool King::validate_move(char row, int col) {
    bool valid_move = Piece::validate_move(row, col);
    bool safe_square = true;

    if(Window::get_board_hitboxes().check_hitbox((team == 'w') ? 'b' : 'w', row, col)) {
        safe_square = false;
    }

    return valid_move && safe_square;
}

void King::update_position(Position pos) {
    if (!already_moved) {
        already_moved = true;
    }

    Piece::update_position(pos);
}

bool King::is_in_check() {
    return Window::get_board_hitboxes().check_hitbox((team == 'w') ? 'b' : 'w', piece_position);
}


/*
    OVERLOADED FUNCTIONS
*/

bool King::validate_move(Position pos) {
    return validate_move(pos.first, pos.second);
}