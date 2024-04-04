#include "hitbox_manager.hpp"

#include "piece.hpp"
#include "hitbox.hpp"

Hitbox_Manager::Hitbox_Manager(Board& board) :
    game_board(board)
{}
Hitbox_Manager::~Hitbox_Manager(){}

std::vector<std::shared_ptr<Hitbox>> Hitbox_Manager::check_hitbox(Color team, char row, int col) const {
    auto team_board = HITBOX_STATES.find(team);

    if (team_board == HITBOX_STATES.end()) return {};

    auto &board = team_board->second;
    auto hitbox = board.find({row, col});

    if (hitbox != board.end()) return hitbox->second;

    return {};
}

void Hitbox_Manager::remove_hitboxes_from_state(std::shared_ptr<Piece> piece_hitbox_to_update) {
    auto& teamHitboxes = HITBOX_STATES[piece_hitbox_to_update->get_team()];

    for (const auto& each : piece_hitbox_to_update->get_hitboxes()) {
        auto mapIt = teamHitboxes.find(each->get_position());

        if (mapIt != teamHitboxes.end()) {
            auto& vec = mapIt->second;
            auto vecIt = std::find(vec.begin(), vec.end(), *each);
            if (vecIt != vec.end()) {
                vec.erase(vecIt);
            }
        }
    }
}

void Hitbox_Manager::add_moves_to_state(std::shared_ptr<Piece> piece, std::vector<std::queue<std::shared_ptr<Hitbox>>> moves) {
    Color team = piece->get_team();

    for (auto& queue : moves) {
        if (queue.empty()) continue;
        while(!queue.empty()) {
            std::shared_ptr<Hitbox> curr_hitbox = queue.front();
            queue.pop();
            HITBOX_STATES[team][curr_hitbox->get_position()].push_back(curr_hitbox);
            piece->add_hitbox(curr_hitbox);
        }
    }
}

/*
    OVERLOADED FUNCTIONS
*/
 
std::vector<std::shared_ptr<Hitbox>> Hitbox_Manager::check_hitbox(Color team, const Position& key) const {
    return check_hitbox(team, key.row, key.col);
}

std::vector<std::shared_ptr<Hitbox>> Hitbox_Manager::check_hitbox(const Position& pos) const {
    std::vector<std::shared_ptr<Hitbox>> mergedResults;
    
    if (HITBOX_STATES.empty()) return mergedResults;

    for (auto &each_board : HITBOX_STATES) {
        if (each_board.second.empty()) continue;

        auto iter = each_board.second.find(pos);
        if (iter != each_board.second.end() && !iter->second.empty()) mergedResults.insert(mergedResults.end(), iter->second.begin(), iter->second.end());
    }

    return mergedResults;
}