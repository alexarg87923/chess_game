#pragma once

#include "board.hpp"
#include "chess_ai.hpp"
#include "hitbox_manager.hpp"

class Piece;

class Move_Handler {
public:
    Move_Handler(Board& incoming_game_board);

    void move_piece(std::__1::shared_ptr<Piece> piece, Position pos);
    void place_piece(std::__1::shared_ptr<Piece> piece);
    void update_piece(std::shared_ptr<Piece> piece);
private:
    Board& game_board;

    Hitbox_Manager hitbox_manager;
    std::map<Position, std::vector<std::shared_ptr<Piece>>> obstruction_manager;

    std::pair<std::vector<Position>, std::vector<std::shared_ptr<Piece>>> check_for_obstructions_and_valid_moves(std::shared_ptr<Piece> inc_piece, std::map<int, std::queue<Position>> moves);
    // void reset_parents_at(const Position pos);
};