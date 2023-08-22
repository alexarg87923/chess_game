#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <map>
#include <vector>
#include "constant.hpp"
#include "board.hpp"

class Piece;
class Hitbox;

class State_Manager {
public:
    State_Manager(Board* board);
    ~State_Manager();

    std::vector<Hitbox*> check_hitbox(Color team, const Position& key) const;
    std::vector<Hitbox*> check_hitbox(Color team, char row, int col) const;

    void clear_hitbox_state();
    void update_hitbox_state(Color team, const Position& pos, Hitbox *value);
    void update_hitbox_state(Color team, char row, int col, Hitbox *value);
    void refresh_hitbox_state(Piece* piece_hitbox_to_update);
    void add_moves_to_state(Piece* piece);
    std::vector<Hitbox*> check_hitbox(const Position& pos) const;

private:
    std::map<char, std::map<Position, std::vector<Hitbox*>>> HITBOX_STATES;
    Board* game_board;
};

#endif
