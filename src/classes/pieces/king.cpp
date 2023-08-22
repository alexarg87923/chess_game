#include "pieces/king.hpp"

King::King(const Position& pos, Color team_color, sf::Vector2f size, Move_Handler& handler) : King(pos.row, pos.col, team_color, size, handler) {}
King::King(char row, int col, Color team_color, sf::Vector2f size, Move_Handler& handler) : Piece(row, col, team_color, "king", size, handler) {
    valid_moves = get_moves(piece_position);
}

std::vector<Position> King::get_moves(const Position& pos, bool get_every_move) const {
    const int RANGE_START = -1;
    const int RANGE_END = 2;
    const int ZERO_OFFSET = 0;

    std::vector<Position> moves;
    Position pos_copy = pos;
    
    for (int i = RANGE_START; i < RANGE_END; i++) {
        for (int j = RANGE_START; j < RANGE_END; j++) {
            Position new_pos = {static_cast<char>(pos_copy.row + i), pos_copy.col + j};
            if (!(i == ZERO_OFFSET && j == ZERO_OFFSET)) {
                if (validate_move(new_pos))
                    moves.push_back(new_pos);
            }
        }
    }

    return moves;
}


bool King::validate_move(char row, int col) const {
    bool valid_move = Piece::validate_move(row, col);
    bool safe_square = true;

    // if(Game::get_hitbox_states().check_hitbox((team == 'w') ? 'b' : 'w', row, col)) {
    //     safe_square = false;
    // }

    return valid_move && safe_square;
}

// bool King::is_in_check() const {
//     // return (Game::get_hitbox_states()->check_hitbox((team == 'w') ? 'b' : 'w', piece_position).empty() ? false : true);
// }


/*
    OVERLOADED FUNCTIONS
*/

bool King::validate_move(const Position& pos) const {
    return validate_move(pos.row, pos.col);
}