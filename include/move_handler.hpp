#pragma once

#include "board.hpp"
#include "chess_ai.hpp"
#include "hitbox_manager.hpp"
#include "piece.hpp"
#include <glog/logging.h>

#include <set>

class Piece;

class Move_Handler {
public:
    Move_Handler(Board& incoming_game_board);

    void move_piece(std::shared_ptr<Piece> piece, Position pos);
    void place_piece(std::shared_ptr<Piece> piece);

private:
    Board& game_board;

    Hitbox_Manager hitbox_manager;

    // std::map<Position, std::vector<std::shared_ptr<Piece>>> obstructing_pieces_manager;
    std::map<Position, std::vector<std::shared_ptr<Piece>>> obstructed_pieces_manager;

    std::vector<std::shared_ptr<Piece>> re_process_list;
    // std::set<std::shared_ptr<Piece>> processed_pieces;

    // std::map<Color, std::vector<std::queue<Position>>> squares_between;

    void check_for_obstructions_and_valid_moves(std::shared_ptr<Piece> inc_piece, std::vector<std::queue<std::shared_ptr<Hitbox>>> moves);
    void reset_hitboxes(std::shared_ptr<Piece> piece);
    void reset_obstructed_at(const Position pos);
    void process_list();

    std::vector<std::queue<std::shared_ptr<Hitbox>>> check_cache_or_calculate(Position pos, std::shared_ptr<Piece>& piece);

    // void update_obstructed_pieces(Position pos);

    // void add_obstructed(const Position pos, std::shared_ptr<Piece> piece);
    void check_if_im_obstructing(const Position pos);

    // void simulate_update();

    // bool is_in_squares_between(const Position& pos, Color team);

};