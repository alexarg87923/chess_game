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
    auto position = piece->get_pos();

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
    auto pos = p.get_pos(); // position to set it to
    
    reset_hitboxes(piece); // reset the hitboxes if there are any

    // check for cached moves
    std::map<MoveAttributes, std::vector<std::queue<Position>>> moves = check_cache(pos, piece);

    // look for valid moves
    std::vector<Position> valid_moves = check_for_obstructions_and_valid_moves(piece, moves);

    // add the valid moves to the hitbox manager
    hitbox_manager.add_moves_to_state(piece, valid_moves);

    // update the pieces that need updating now
    update_deferred_pieces();

    // clear the queue
    processed_pieces.clear();
}

void Move_Handler::update_deferred_pieces() {
    while (!deferred_pieces.empty()) {
        auto piece_to_place = deferred_pieces.front();
        deferred_pieces.pop();
        place_piece(piece_to_place);
    }
}

void Move_Handler::simulate_update() {
    std::queue<std::shared_ptr<Piece>> temp_queue = deferred_pieces;

    while (!temp_queue.empty()) {
        auto piece_to_place = temp_queue.front();
        temp_queue.pop();
        place_piece(piece_to_place);
    }
}

std::vector<Position> Move_Handler::check_for_obstructions_and_valid_moves(std::shared_ptr<Piece> inc_piece, std::map<MoveAttributes, std::vector<std::queue<Position>>> moves) {
    std::vector<Position> valid_moves;
    std::queue<Position> temp_queue;

    if (squares_between.size() > 1 && !inc_piece->is_king()) {
        return valid_moves;
    }

    for (auto & moves_pair : moves) {
        if (!moves_pair.second.empty()) {
            for (auto & queue : moves_pair.second) {
                std::queue<Position> move_queue;
    
                while (!queue.empty()) {
                    const Position& next_pos = queue.front();
                    auto piece_opt = game_board.get_piece(next_pos);
                    MoveAttributes move_attr = moves_pair.first;

                    if (squares_between.size() == 1 && move_attr == MoveAttributes::SEARCH && !inc_piece->is_king() && is_in_squares_between(next_pos)) {
                        valid_moves.push_back(next_pos);
                        queue.pop();
                    } else if (squares_between.size() == 0) {
                        if (piece_opt.has_value()) {
                            std::shared_ptr<Piece> piece = piece_opt.value();
                            Color team = inc_piece->get_team();

                            if (piece->get_team() != team &&
                                (move_attr == MoveAttributes::VALID_ON_ENEMY_ONLY || move_attr == MoveAttributes::SEARCH)) {
                                valid_moves.push_back(next_pos);
                            }

                            add_obstructed(next_pos, inc_piece);

                            // This is checking for king
                            if (piece == game_board.get_king((team == BLACK ? WHITE : BLACK))) {
                                squares_between.push_back(move_queue);
                                break;
                            }

                            move_queue.push(queue.front());
                            queue.pop();

                            break;
                        } else if (move_attr == MoveAttributes::OBSTRUCT_ON_OCCUPY || move_attr == MoveAttributes::SEARCH) {
                            valid_moves.push_back(next_pos);
                            move_queue.push(queue.front());
                            queue.pop();
                        } else {
                            move_queue.push(queue.front());
                            queue.pop();
                        }
                    } else {
                        valid_moves.push_back(next_pos);
                        move_queue.push(queue.front());
                        queue.pop();
                    }
                }
            }
        }
    }

    return valid_moves;
}

std::map<MoveAttributes, std::vector<std::queue<Position>>> Move_Handler::check_cache(Position pos, std::shared_ptr<Piece> piece) {
    Piece& p = *piece;

    if (p.moves_are_valid()) {
        return p.get_moves();
    } else {
        auto moves = p.calc_moves(pos);
        p.cache_moves(moves);
        game_board.set_piece(pos, piece);
        check_if_im_obstructing(pos, piece);
        reset_obstructed_at(pos);
        return moves;
    }
}

void Move_Handler::reset_obstructed_at(const Position pos) {    
    if (obstructed_pieces_manager.find(pos) != obstructed_pieces_manager.end()) {
        auto& obstructed_pieces = obstructed_pieces_manager[pos];
        for (const auto& obstructing_piece : obstructed_pieces) {
            if (processed_pieces.find(obstructing_piece) == processed_pieces.end()) {
                deferred_pieces.push(obstructing_piece);
                processed_pieces.insert(obstructing_piece);
            }
        }
        obstructed_pieces_manager.erase(pos);
    }
}


void Move_Handler::check_if_im_obstructing(const Position pos, std::shared_ptr<Piece> piece) {
    auto hitboxes = hitbox_manager.check_hitbox(pos);

    if (!hitboxes.empty()) {
        for (auto const & hitbox : hitboxes) {
            add_obstructed(pos, hitbox->get_parent());
        }
    }
}

void Move_Handler::add_obstructed(const Position pos, std::shared_ptr<Piece> piece) {
    obstructed_pieces_manager[pos].emplace_back(piece);
}

bool Move_Handler::hitbox_in_pos_of_king(Color team) {
    return !hitbox_manager.check_hitbox(game_board.get_king(team)->get_pos()).empty();
}

bool Move_Handler::is_in_squares_between(const Position& pos) {
    for (const auto& queue : squares_between) {
        std::queue<Position> temp = queue;  // Create a copy to iterate through
        while (!temp.empty()) {
            if (temp.front() == pos) return true;
            temp.pop();
        }
    }
    return false;
}