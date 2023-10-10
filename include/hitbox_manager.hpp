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

    void remove_hitboxes_from_state(std::shared_ptr<Piece> piece_hitbox_to_update);
    void add_moves_to_state(std::shared_ptr<Piece> piece, std::vector<std::queue<std::shared_ptr<Hitbox>>> moves);
    std::vector<std::shared_ptr<Hitbox>> check_hitbox(const Position& pos) const;

private:
    std::map<Color, std::map<Position, std::vector<std::shared_ptr<Hitbox>>>> HITBOX_STATES;
    Board& game_board;
};
