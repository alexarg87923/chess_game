#include "pieces/bishop.hpp"

Bishop::Bishop(const Position& pos, Color team_color, sf::Vector2f size, Move_Handler& handler) : Bishop(pos.row, pos.col, team_color, size, handler) {}
Bishop::Bishop(char row, int col, Color team_color, sf::Vector2f size, Move_Handler& handler) : Piece(row, col, team_color, "bishop", size, handler) {
    valid_moves = get_moves(piece_position);
}

std::vector<Position> Bishop::get_moves(const Position& pos, bool get_every_move) const {
    char row_begin = pos.row, row_end = 7 + 'A';
    int col_begin = pos.col, col_end = BOARD_COL;

    int j = col_begin + 1;

    std::vector<Position> all_moves;    

    // TOP LEFT
    for (char i = row_begin - 1, j = col_begin + 1; i >= 'A' && j <= BOARD_COL; i--, j++) {
        all_moves.push_back({i, j});
        if (move_handler.is_there_obstruction(Position{i, j}) && !get_every_move)
            break;
    }

    // TOP RIGHT
    for (char i = row_begin + 1, j = col_begin + 1; i <= 'H' && j <= BOARD_COL; i++, j++) {
        all_moves.push_back({i, j});
        if (move_handler.is_there_obstruction(Position{i, j}) && !get_every_move)
            break;
    }

    // BOTTOM RIGHT
    for (char i = row_begin + 1, j = col_begin - 1; i <= 'H' && j > 0; i++, j--) {
        all_moves.push_back({i, j});
        if (move_handler.is_there_obstruction(Position{i, j}) && !get_every_move)
            break;
    }

    // BOTTOM LEFT
    for (char i = row_begin - 1, j = col_begin - 1; i >= 'A' && j > 0; i--, j--) {
        all_moves.push_back({i, j});
        if (move_handler.is_there_obstruction(Position{i, j}) && !get_every_move)
            break;
    }

    return all_moves;
}
