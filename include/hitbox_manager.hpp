#pragma once

#include <map>
#include <queue>
#include "constants.hpp"
#include "board.hpp"

class Piece;
class Hitbox;

class Hitbox_Manager {
public:
    Hitbox_Manager(Board& board);
    ~Hitbox_Manager();

    std::vector<std::shared_ptr<Hitbox>> check_hitbox(Color team, const Position& key) const;
    std::vector<std::shared_ptr<Hitbox>> check_hitbox(Color team, char row, int col) const;

    // void clear_hitbox_state();
    void update_hitbox_state(Color team, const Position& pos, std::shared_ptr<Hitbox> value);
    void update_hitbox_state(Color team, char row, int col, std::shared_ptr<Hitbox> value);
    void remove_hitboxes_from_state(std::shared_ptr<Piece> piece_hitbox_to_update);
    void add_moves_to_state(std::shared_ptr<Piece> piece, std::vector<Position> moves);
    std::vector<std::shared_ptr<Hitbox>> check_hitbox(const Position& pos) const;

private:
    std::map<char, std::map<Position, std::vector<std::shared_ptr<Hitbox>>>> HITBOX_STATES;
    Board& game_board;
};
