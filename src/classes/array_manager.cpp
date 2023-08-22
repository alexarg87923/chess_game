#include "array_manager.hpp"

#include "piece.hpp"

Array_Manager::Array_Manager(){}
Array_Manager::~Array_Manager(){}

bool Array_Manager::check_hitbox(char team, char row, int col) {
    return CHECK_HITBOX_FAST[team][row - 'A'][BOARD_COL - col];
}

void Array_Manager::clear_check_hitbox() {
    for (auto &pair : CHECK_HITBOX_FAST) {
        for(auto &row : CHECK_HITBOX_FAST[pair.first]) {
            std::fill(std::begin(row), std::end(row), false);
        }
    }
}

void Array_Manager::update_check_hitbox(char team, char row, int col, bool value) {
    CHECK_HITBOX_FAST[team][row - 'A'][BOARD_COL - col] = value;
}

void Array_Manager::refresh_check_hitbox(std::map<Position, Piece *> currBoard) {
    Array_Manager::clear_check_hitbox();
    char team;

    for (const auto &pair: currBoard) {
        team = pair.second->get_team();
        for (const auto &move: pair.second->get_moves(pair.first, true)) {
            update_check_hitbox(team, move.first, move.second, true);
        }
    }
}

/*
    OVERLOADED FUNCTIONS
*/

bool Array_Manager::check_hitbox(char team, Position key) {
    return check_hitbox(team, key.first, key.second);
}