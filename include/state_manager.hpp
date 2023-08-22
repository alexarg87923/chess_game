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
    State_Manager();
    ~State_Manager();

    std::vector<Hitbox> check_hitbox(char team, Position key);
    std::vector<Hitbox> check_hitbox(char team, char row, int col);
    void clear_hitbox_state();
    void update_hitbox_state(char team, Position pos, Hitbox value);
    void update_hitbox_state(char team, char row, int col, Hitbox value);
    void refresh_hitbox_state(Piece* piece_hitbox_to_update);
private:
    std::map<char, std::map<Position, std::vector<Hitbox>>> HITBOX_STATES;
};

#endif
