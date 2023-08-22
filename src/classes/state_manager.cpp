#include "state_manager.hpp"

#include "piece.hpp"
#include "hitbox.hpp"

State_Manager::State_Manager(){}
State_Manager::~State_Manager(){}

std::vector<Hitbox*> State_Manager::check_hitbox(char team, char row, int col) {
    return HITBOX_STATES[team][std::make_pair(row - 'A', BOARD_COL - col)];
}

void State_Manager::clear_hitbox_state() {
    for (auto &pair : HITBOX_STATES) {
        for(auto &pair2 : HITBOX_STATES[pair.first]) {
            pair2.second.clear();
        }
    }
}

void State_Manager::update_hitbox_state(char team, char row, int col, Hitbox *value) {
    HITBOX_STATES[team][std::make_pair(row, col)].push_back(value);
}

void State_Manager::refresh_hitbox_state(Piece* piece_hitbox_to_update) {
    auto& teamHitboxes = HITBOX_STATES[piece_hitbox_to_update->get_team()];

    for (const auto& each : piece_hitbox_to_update->get_hitboxes()) {
        auto mapIt = teamHitboxes.find(each->get_position());

        if (mapIt != teamHitboxes.end()) {
            auto& vec = mapIt->second;
            auto vecIt = std::remove(vec.begin(), vec.end(), *each);
            vec.erase(vecIt, vec.end());
        }
    }

    piece_hitbox_to_update->clear_hitboxes();

    add_moves_to_state(piece_hitbox_to_update);
}
// TO DO
// CALL THIS AFTER VALID MOVES OF A PIECE ARE CALCULATED, 
void State_Manager::add_moves_to_state(Piece* piece) {
    for (auto &each : piece->get_valid_moves()) {
        update_hitbox_state(piece->get_team(), each, new Hitbox(Board::get_size_of_grid_square(), each, Board::pair_to_pos(each), (Board::check_piece(each) ? sf::Color(0, 0, 255, 128) : sf::Color(0, 0, 255)), piece));
    }
}

/*
    OVERLOADED FUNCTIONS
*/

std::vector<Hitbox*> State_Manager::check_hitbox(char team, Position key) {
    return check_hitbox(team, key.first, key.second);
}

void State_Manager::update_hitbox_state(char team, Position pos, Hitbox *value) {
    HITBOX_STATES[team][pos].push_back(value);
}