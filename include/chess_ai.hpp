#ifndef CHESS_AI_H
#define CHESS_AI_H

#include <map>

#include "constant.hpp"
#include "state_manager.hpp"
#include "types.hpp"

class Chess_AI {
public:
    Chess_AI();
    ~Chess_AI();
    bool will_this_move_stop_check(State_Manager board, Position pos);
};

#endif
