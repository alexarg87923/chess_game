#include "move_handler.hpp"

Move_Handler::Move_Handler(Board& incoming_game_board) :
    game_board(incoming_game_board), hitbox_manager(game_board)
{}

void Move_Handler::move_piece(std::shared_ptr<Piece> piece, Position pos) {
    // auto position = piece->get_pos();

    // game_board.set_piece(position, nullptr);

    // game_board.set_piece(pos, piece);

    // reset_obstructed_at(position);
    // simulate_update();

    // if (hitbox_in_pos_of_king(piece->get_team())) {
    //     game_board.set_piece(position, piece);
    // } else {
    //     piece->set_piece_pos(pos);
    // }

    // piece->invalidate_moves();

    // place_piece(piece);
    Position position = piece->get_pos();

    game_board.set_piece(position, nullptr);
    piece->set_piece_pos(pos);

    reset_obstructed_at(position);

    piece->invalidate_moves();

    place_piece(piece);
}

void Move_Handler::reset_hitboxes(std::shared_ptr<Piece> piece) {
    Piece& p = *piece;

    hitbox_manager.remove_hitboxes_from_state(piece);
    p.clear_hitboxes();
}

void Move_Handler::place_piece(const std::shared_ptr<Piece> piece) {
    Piece& p = *piece;
    Position pos = p.get_pos(); // position to set it to
    
    reset_hitboxes(piece); // reset the hitboxes if there are any

    // check for cached moves
    std::map<MoveAttributes, std::vector<std::queue<Position>>> moves = check_cache(pos, piece);

    // add the valid moves to the hitbox manager
    // hitbox_manager.add_moves_to_state(piece, );

    // look for valid moves
    std::vector<Position> valid_moves = check_for_obstructions_and_valid_moves(piece, moves);

    // update the pieces that need updating now
    // update_deferred_pieces();

    // clear the queue
    // processed_pieces.clear();
}

std::map<MoveAttributes, std::vector<std::queue<Position>>> Move_Handler::check_cache(Position pos, std::shared_ptr<Piece> piece) {
    Piece& p = *piece;

    if (p.moves_are_valid()) {
        return p.get_moves();
    } else {
        std::map<MoveAttributes, std::vector<std::queue<Position>>> moves = p.calc_moves(pos);
        p.cache_moves(moves);
        game_board.set_piece(pos, piece);
        // check_if_im_obstructing(pos, piece);
        // reset_obstructed_at(pos);
        return moves;
    }
}

std::vector<Position> Move_Handler::check_for_obstructions_and_valid_moves(std::shared_ptr<Piece> inc_piece, std::map<MoveAttributes, std::vector<std::queue<Position>>> moves) {
    std::vector<Position> valid_moves;
    std::queue<Position> temp_queue;
    Color team = inc_piece->get_team();
    bool is_king = inc_piece->is_king();
    Color opposite_team = (team == BLACK) ? WHITE : BLACK;

    if (squares_between[team].size() > 1 && !is_king) {
        return valid_moves;
    }

    for (std::pair<const MoveAttributes, std::vector<std::queue<Position>>> & moves_pair : moves) {
        if (moves_pair.second.empty()) continue;

        for (std::queue<Position>& queue : moves_pair.second) {
            std::queue<Position> move_queue;

            while (!queue.empty()) {
                Position& curr_pos = queue.front();
                MoveAttributes move_attr = moves_pair.first;

                // hitbox_manager.add_move_to_state(inc_piece, curr_pos, );

                if (move_attr == MoveAttributes::KING) {
                    if (hitbox_manager.check_hitbox(curr_pos).empty()) {
                        valid_moves.push_back(curr_pos);
                        queue.pop();
                    }
                    continue;
                }

                if (squares_between[team].size() == 1) {
                    if (move_attr == MoveAttributes::SEARCH && is_in_squares_between(curr_pos, team) && !is_king) {
                        valid_moves.push_back(curr_pos);
                        queue.pop();
                        continue;
                    }
                } else if (squares_between[team].size() == 0) {
                    std::optional<std::__1::shared_ptr<Piece>> piece_opt = game_board.get_piece(curr_pos);
                    if (piece_opt.has_value()) {
                        std::shared_ptr<Piece> piece = piece_opt.value();

                        curr_pos.has_piece = true;

                        if (piece->get_team() != team &&
                            (move_attr == MoveAttributes::VALID_ON_ENEMY_ONLY || move_attr == MoveAttributes::SEARCH)) {
                            valid_moves.push_back(curr_pos);
                        }

                        add_obstructed(curr_pos, inc_piece);

                        // This is checking for king
                        if (piece == game_board.get_king(opposite_team)) {
                            place_piece(piece);
                            squares_between[opposite_team].push_back(move_queue);
                            break;
                        }

                        move_queue.push(curr_pos);
                        queue.pop();
                        break;
                    } else if (move_attr == MoveAttributes::OBSTRUCT_ON_OCCUPY || move_attr == MoveAttributes::SEARCH) {
                        valid_moves.push_back(curr_pos);
                        move_queue.push(curr_pos);
                        queue.pop();
                        continue;
                    }
                }
            }
        }
    }



    return valid_moves;
}

void Move_Handler::check_if_im_obstructing(const Position pos, std::shared_ptr<Piece> piece) {
    // std::vector<std::shared_ptr<Hitbox>> hitboxes = hitbox_manager.check_hitbox(pos);
    // if (hitboxes.empty()) return;

    // for (std::shared_ptr<Hitbox> const & hitbox : hitboxes) {
    //     add_obstructed(pos, hitbox->get_parent());
    // }
}

void Move_Handler::reset_obstructed_at(const Position pos) {    
    // if (obstructed_pieces_manager.find(pos) == obstructed_pieces_manager.end()) return;

    // std::vector<std::shared_ptr<Piece>>& obstructed_pieces = obstructed_pieces_manager[pos];

    // for (const std::shared_ptr<Piece>& obstructing_piece : obstructed_pieces) {
    //     if (processed_pieces.find(obstructing_piece) != processed_pieces.end()) continue;

    //     deferred_pieces.push(obstructing_piece);
    //     processed_pieces.insert(obstructing_piece);
    // }
    // obstructed_pieces_manager.erase(pos);
}

void Move_Handler::update_deferred_pieces() {
    // while (!deferred_pieces.empty()) {
    //     std::shared_ptr<Piece> piece_to_place = deferred_pieces.front();
    //     deferred_pieces.pop();
    //     place_piece(piece_to_place);
    // }
}

void Move_Handler::simulate_update() {
    // std::queue<std::shared_ptr<Piece>> temp_queue = deferred_pieces;

    // while (!temp_queue.empty()) {
    //     std::shared_ptr<Piece>  piece_to_place = temp_queue.front();
    //     temp_queue.pop();
    //     place_piece(piece_to_place);
    // }
}

void Move_Handler::add_obstructed(const Position pos, std::shared_ptr<Piece> piece) {
    // obstructed_pieces_manager[pos].emplace_back(piece);
}

bool Move_Handler::is_in_squares_between(const Position& pos, Color team) {
    // for (const std::queue<Position>& queue : squares_between[team]) {
    //     std::queue<Position> temp = queue;  // Create a copy to iterate through
    //     while (!temp.empty()) {
    //         if (temp.front() == pos) return true;
    //         temp.pop();
    //     }
    // }
    return true;
}