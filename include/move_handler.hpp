#pragma once

#include "board.hpp"
#include "chess_ai.hpp"
#include "hitbox_manager.hpp"

#include <queue>
#include <set>

class Piece;

class Move_Handler {
public:
    Move_Handler(Board& incoming_game_board);

    void move_piece(std::__1::shared_ptr<Piece> piece, Position pos);
    void place_piece(std::__1::shared_ptr<Piece> piece);

private:
    Board& game_board;

    Hitbox_Manager hitbox_manager;

    std::map<Position, std::vector<std::shared_ptr<Piece>>> obstructing_pieces_manager;
    std::map<Position, std::vector<std::shared_ptr<Piece>>> obstructed_pieces_manager;

    std::queue<std::shared_ptr<Piece>> deferred_pieces;
    std::set<std::shared_ptr<Piece>> processed_pieces;

    std::vector<Position> check_for_obstructions_and_valid_moves(std::shared_ptr<Piece> inc_piece, std::map<MoveAttributes, std::vector<std::queue<Position>>> moves);
    void reset_hitboxes(std::shared_ptr<Piece> piece);
    void reset_obstructed_at(const Position pos);

    std::map<MoveAttributes, std::vector<std::queue<Position>>> check_cache(Position pos, std::shared_ptr<Piece> piece);

    void update_deferred_pieces();

    void add_obstructed(const Position pos, std::shared_ptr<Piece> piece);
    void check_if_im_obstructing(const Position pos, std::shared_ptr<Piece> piece);
};