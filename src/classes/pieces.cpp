#include "piece.hpp"

#include "board.hpp"
#include "pieces/king.hpp"
#include "game.hpp"
#include "hitbox.hpp"

Piece::Piece(char row, int col, char team_color) : Piece(std::make_pair(row, col), team_color) {}
Piece::Piece(Position pos, char team_color) {
    team = team_color;
    save_piece(new sf::RectangleShape(Board::get_size_of_grid_square()));
    set_position(pos);
}

void Piece::save_piece_to_map(char team, std::string name, Piece* piece) {
    Board::save_map_of_pieces(team, name, piece);
}

void Piece::draw(sf::RenderTarget& target) const {
    target.draw(*piece);
}

std::vector<Position> Piece::get_valid_moves() {
    return valid_moves;
}

void Piece::save_piece(sf::RectangleShape *tmp) {
    piece = tmp;
}

Position Piece::get_pos() {
    return piece_position;
}

sf::RectangleShape *Piece::get_piece() {
    return piece;
}

void Piece::update_position(Position pos) {
    set_position(pos);
}

void Piece::set_position(Position &pos) {
    if(piece_position.first) {
        Board::set_piece(piece_position);
    }

    auto curr_state = Game::get_hitbox_states();

    auto hitboxes_at_old_pos = curr_state->check_hitbox(piece_position);

    piece_position = pos;
    Board::set_piece(piece_position, this);
    piece->setPosition(Board::pair_to_pos(piece_position));

    auto hitboxes_at_new_pos = curr_state->check_hitbox(piece_position);

    hitboxes_at_new_pos.insert(hitboxes_at_new_pos.end(), hitboxes_at_old_pos.begin(), hitboxes_at_old_pos.end());

    refresh_affected_pieces(hitboxes_at_new_pos);
}

void Piece::refresh_affected_pieces(const std::vector<Hitbox*>& affected_hitboxes) {
    if (affected_hitboxes.empty()) return;

    auto curr_state = Game::get_hitbox_states();

    for (const auto& hitbox : affected_hitboxes) {
        curr_state->refresh_hitbox_state(hitbox->get_parent());
    }
}


bool Piece::validate_move(char row, int col) {
    // If position is out of bounds, return false, else true
    if (row > 'H' || row < 'A' || col > 8 || col < 1) {
        return false;
    } else {
        return true;
    }
}

std::string Piece::get_working_dir() {
    char buffer[FILENAME_MAX];
    if (getcwd(buffer, sizeof(buffer)) != nullptr) {
        //std::cout << "Current working directory: " << buffer << std::endl;
        return std::string(buffer);
    } else {
        std::cerr << "Failed to get the current working directory." << std::endl;
        return "";
    }
}

sf::Texture* Piece::load_sprite(const std::string& name, char team_color) {
    sf::Texture* sprite = new sf::Texture();
    sprite->loadFromFile(get_working_dir() + "/src/assets/images/" + name + '_' + std::string(1, team_color) + ".png");
    return sprite;
}

bool Piece::is_king_in_check() {
    King* king = dynamic_cast<King*>(Board::get_piece_from_map(team, "king"));
    if(king != nullptr) {
        return king->is_in_check();
    }
    return false;
}

void Piece::calc_valid_moves() {
    Game::get_hitbox_states()->add_moves_to_state(this);
}

char Piece::get_team() {
    return team;
}

bool Piece::is_this_move_going_to_stop_check(Position move) {
    return false;
    if(!is_king_in_check())
        return false;

    Chess_AI game_simulation;

    return game_simulation.will_this_move_stop_check(Game::get_hitbox_states(), move);
}

std::vector<Hitbox*> Piece::get_hitboxes() {
    return hitboxes;
}

void Piece::clear_hitboxes() {
    hitboxes.clear();
}

void Piece::add_hitbox(Hitbox *hitbox) {
    hitboxes.push_back(hitbox);
}


/*
    OVERLOADED FUNCTIONS
*/

bool Piece::validate_move(Position pos) {
    return validate_move(pos.first, pos.second);
}