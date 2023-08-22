#include "pieces/rook.hpp"

Rook::Rook(const Position& pos, Color team_color, sf::Vector2f size, Move_Handler& handler) : Rook(pos.row, pos.col, team_color, size, handler) {}
Rook::Rook(char row, int col, Color team_color, sf::Vector2f size, Move_Handler& handler) : Piece(row, col, team_color, "rook", size, handler) {
    valid_moves = get_moves(piece_position);
}

std::vector<Position> Rook::get_moves(const Position& pos) const {
    char row_begin = pos.row, row_end = 7 + 'A';
    int col_begin = pos.col, col_end = BOARD_COL;

    std::vector<Position> moves;

    // LEFT
    row_begin--;
    for (char i = row_begin; i >= 'A'; i--) {
        moves.push_back({i, pos.col});
        if (move_handler.is_there_obstruction(Position{i, pos.col}))
            break;
    }
    // UP
    col_begin++;
    for (int i = col_begin; i <= col_end; i++) {
        moves.push_back({pos.row, i});
        if (move_handler.is_there_obstruction(Position{pos.row, i}))
            break;
    }

    row_begin = pos.row;
    col_begin = pos.col;

    // RIGHT
    row_begin++;
    for (char i = row_begin; i <= row_end; i++) {
        moves.push_back({i, pos.col});
        if (move_handler.is_there_obstruction(Position{i, pos.col}))
            break;
    }
    
    // DOWN
    col_begin--;
    for (int i = col_begin; i >= 1; i--) {
        moves.push_back({pos.row, i});
        if (move_handler.is_there_obstruction(Position{pos.row, i}))
            break;
    }

    return moves;
}