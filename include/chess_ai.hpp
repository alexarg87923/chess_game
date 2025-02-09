#ifndef CHESS_AI_H
#define CHESS_AI_H

#include <map>

#include "constants.hpp"
#include "types.hpp"
#include "move_handler.hpp"

class Chess_AI {
public:
    bool will_this_move_stop_check() const;
};

#endif
