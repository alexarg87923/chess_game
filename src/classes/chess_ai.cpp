#include "chess_ai.hpp"

Chess_AI::Chess_AI(){}
Chess_AI::~Chess_AI(){}

bool Chess_AI::will_this_move_stop_check(Array_Manager board, Position pos) {
    board.clear_check_hitbox();



    return false;
}