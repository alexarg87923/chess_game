#include "move_handler.hpp"

Move_Handler::Move_Handler(Board& incoming_game_board) :
    game_board(incoming_game_board), hitbox_manager(game_board)
{}

void Move_Handler::move_piece(std::shared_ptr<Piece> piece, Position pos) {
    auto position = piece->get_pos(); // get old pos

    game_board.set_piece(position, nullptr); // clear the old position of the piece

    reset_obstructed_at(position); // if pieces were being obstructed, now that i removed the piece from the board, i can recalculate
                                    // and see if the piece is still obstructed

    piece->set_piece_pos(pos); // set the configuratoin of the piece

    piece->invalidate_moves(); // since piece now has a new position then old moves are invalid

    place_piece(piece); // place the piece on the state manager
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

std::vector<Position> Move_Handler::check_for_obstructions_and_valid_moves(std::shared_ptr<Piece> inc_piece, std::map<MoveAttributes, std::vector<std::queue<Position>>> moves) {
    std::vector<Position> valid_moves;

    for (auto & moves_pair : moves) {
        if (!moves_pair.second.empty()) {
            for (auto & queue : moves_pair.second) {
                while (!queue.empty()) {
                    const Position& nextPos = queue.front();
                    auto pieceOpt = game_board.get_piece(nextPos);

                    if (moves_pair.first == MoveAttributes::OBSTRUCT_ON_OCCUPY) {
                        if (pieceOpt.has_value()) {
                            add_obstructed(nextPos, inc_piece);
                            break;
                        } else {
                            valid_moves.push_back(nextPos);
                        }
                    } else if (moves_pair.first == MoveAttributes::VALID_ON_ENEMY_ONLY && pieceOpt.has_value()) {
                        auto piece = pieceOpt.value();
                        if (piece->get_team() != inc_piece->get_team()) {
                            valid_moves.push_back(nextPos);
                        }
                        add_obstructed(nextPos, inc_piece);
                        break; // stop checking further in this direction as there's an obstruction
                    } else if (moves_pair.first == MoveAttributes::SEARCH) {
                        if (pieceOpt.has_value()) {
                            auto piece = pieceOpt.value();
                            if (piece->get_team() != inc_piece->get_team()) {
                                valid_moves.push_back(nextPos);
                            }
                            add_obstructed(nextPos, inc_piece);
                            break; // stop checking further in this direction as there's an obstruction
                        } else {
                            valid_moves.push_back(nextPos);
                        }
                    }
                    queue.pop(); // move to the next position in this direction
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