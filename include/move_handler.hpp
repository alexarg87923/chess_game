#pragma once

#include "board.hpp"
#include "piece.hpp"
#include "game.hpp"



class Move_Handler {
public:
    Move_Handler(Board* board);
    ~Move_Handler();


private:
    Board* game_board;
};