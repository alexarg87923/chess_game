#pragma once

#include "board.hpp"
#include "chess_ai.hpp"
#include "state_manager.hpp"

class Piece;

class Move_Handler {
public:
    Move_Handler(Board& incoming_game_board, State_Manager& incoming_state_manager);

    void move_piece(std::__1::shared_ptr<Piece> piece, Position pos);
    void place_piece(std::__1::shared_ptr<Piece> piece);
    void update_piece(std::shared_ptr<Piece> piece);

    bool is_there_obstruction(Position pos);
private:
    Board& game_board;
    State_Manager& state_manager;

    std::map<Position, std::vector<std::shared_ptr<Piece>>> obstructionManager;

    void reset_parents_at(const Position pos);
};