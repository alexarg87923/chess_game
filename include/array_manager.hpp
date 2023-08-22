#ifndef ARRAY_MANAGER_H
#define ARRAY_MANAGER_H

#include <map>
#include "constant.hpp"
#include "board.hpp"

class Piece;

class Array_Manager {
public:
    Array_Manager();
    ~Array_Manager();
    bool check_hitbox(char team, Position key);
    bool check_hitbox(char team, char row, int col);
    void clear_check_hitbox();
    void refresh_check_hitbox(std::map<Position, Piece *> currBoard = Board::get_map_of_piece());
    void update_check_hitbox(char team, char row, int col, bool value = false);
private:
    std::unordered_map<char, bool[BOARD_ROW][BOARD_COL]> CHECK_HITBOX_FAST;
};

#endif
