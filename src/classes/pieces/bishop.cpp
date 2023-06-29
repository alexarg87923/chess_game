#include "pieces/bishop.hpp"

Bishop::Bishop(){}
Bishop::~Bishop(){}
Bishop::Bishop(Position pos, char team_color) : Bishop(pos.first, pos.second, team_color) {}
Bishop::Bishop(char row, int col, char team_color) : Piece(row, col, team_color) {
    piece->setTexture(load_sprite(name, team_color));
    calc_valid_moves();
    save_piece_to_map(team, name, this);
}


void Bishop::calc_valid_moves() {
    Piece::calc_valid_moves();

    if (name != "king" && is_king_in_check()) return;

    calculate_bishop_path(position);
    save_moves_globally(name);
}

void Bishop::calculate_bishop_path(Position pos) {
    char row_begin = pos.first, row_end = 7 + 'A';
    int col_begin = pos.second, col_end = BOARD_COL;
    bool do_not_continue = false;
    int j = col_begin + 1;

    // TOP LEFT
    for (char i = row_begin - 1, j = col_begin + 1, do_not_continue = false; i >= 'A' && j <= BOARD_COL; i--, j++) {
        if (!do_not_continue)
            valid_moves.push_back(std::make_pair(i, j));

        if (Board::check_piece(i, j)) {
            Board::update_check_hitbox(team, i, j, true);
            do_not_continue = true;
            break;
        }
    }

    // TOP RIGHT
    for (char i = row_begin + 1, j = col_begin + 1, do_not_continue = false; i <= 'H' && j <= BOARD_COL; i++, j++) {
        if (!do_not_continue)
            valid_moves.push_back(std::make_pair(i, j));

        if (Board::check_piece(i, j)) {
            Board::update_check_hitbox(team, i, j, true);
            do_not_continue = true;
            break;
        }
    }

    // BOTTOM RIGHT
    for (char i = row_begin + 1, j = col_begin - 1, do_not_continue = false; i <= 'H' && j > 0; i++, j--) {
        if (!do_not_continue)
            valid_moves.push_back(std::make_pair(i, j));

        if (Board::check_piece(i, j)) {
            Board::update_check_hitbox(team, i, j, true);
            do_not_continue = true;
            break;
        }
    }

    // BOTTOM LEFT
    for (char i = row_begin - 1, j = col_begin - 1, do_not_continue = false; i >= 'A' && j > 0; i--, j--) {
        if (!do_not_continue)
            valid_moves.push_back(std::make_pair(i, j));

        if (Board::check_piece(i, j)) {
            Board::update_check_hitbox(team, i, j, true);
            do_not_continue = true;
            break;
        }
    }
}

