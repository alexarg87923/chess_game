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

    // reset_obstructed_at(position);

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
    Position pos = p.get_pos();
    
    reset_hitboxes(piece);

    std::vector<std::queue<std::shared_ptr<Hitbox>>> all_hitboxes = check_cache(pos, piece);

    // add all moves to the hitbox manager
    hitbox_manager.add_moves_to_state(piece, all_hitboxes);

    // look for valid moves
    check_for_obstructions_and_valid_moves(piece, all_hitboxes);

    // update the pieces that need updating now
    // update_deferred_pieces();

    // clear the queue
    // processed_pieces.clear();
}

std::vector<std::queue<std::shared_ptr<Hitbox>>> Move_Handler::check_cache(Position pos, std::shared_ptr<Piece> piece) {
    Piece& p = *piece;

    if (p.moves_are_valid()) {
        return p.get_moves();
    } else {
        std::vector<std::queue<std::shared_ptr<Hitbox>>> all_moves = p.calc_moves(pos);
        p.cache_moves(all_moves);
        game_board.set_piece(pos, piece);
        // check_if_im_obstructing(pos, piece);
        // reset_obstructed_at(pos);
        return all_moves;
    }
}

void Move_Handler::check_for_obstructions_and_valid_moves(std::shared_ptr<Piece> inc_piece, std::vector<std::queue<std::shared_ptr<Hitbox>>> moves) {
    PIECE piece = inc_piece->get_piece_type();

    auto pawn_logic = [this](std::vector<std::queue<std::shared_ptr<Hitbox>>>& moves) {
        auto processMoves = [this](std::queue<std::shared_ptr<Hitbox>>& queue, bool isDiagonal) {
            bool continueChecking = true;
            while (!queue.empty() && continueChecking) {
                std::shared_ptr<Hitbox> curr_hitbox = queue.front();
                queue.pop();

                std::optional<std::shared_ptr<Piece>> piece_opt = game_board.get_piece(curr_hitbox->get_position());
                if (isDiagonal) {
                    if (piece_opt.has_value()) {
                        curr_hitbox->highlight();
                    }
                } else {
                    if (!piece_opt.has_value()) {
                        curr_hitbox->show();
                        continueChecking = false;
                    }
                }
            }
        };

        std::queue<std::shared_ptr<Hitbox>>& diagonal = moves[MovementType::DIAGONAL];
        std::queue<std::shared_ptr<Hitbox>>& straight = moves[MovementType::STRAIGHT];

        processMoves(diagonal, true);
        processMoves(straight, false);
    };
    
    auto bishop_queen_rook_logic = [this](std::vector<std::queue<std::shared_ptr<Hitbox>>>& moves) {
        for (auto& queue : moves) {
            while(!queue.empty()) {
                std::shared_ptr<Hitbox> curr_hitbox = queue.front();
                queue.pop();
                std::optional<std::__1::shared_ptr<Piece>> piece_opt = game_board.get_piece(curr_hitbox->get_position());
                if (piece_opt.has_value()) {
                    curr_hitbox->highlight();
                    break;
                }

                curr_hitbox->show();
            }
        }
    };
    auto knight_logic = [this](std::vector<std::queue<std::shared_ptr<Hitbox>>>& moves) {
        for (auto& queue : moves) {
            while(!queue.empty()) {
                std::shared_ptr<Hitbox> curr_hitbox = queue.front();
                queue.pop();
                std::optional<std::__1::shared_ptr<Piece>> piece_opt = game_board.get_piece(curr_hitbox->get_position());
                if (piece_opt.has_value()) {
                    curr_hitbox->highlight();
                }
            }
        }
    };
    auto king_logic = [this, inc_piece](std::vector<std::queue<std::shared_ptr<Hitbox>>>& moves) {
        for (auto& queue : moves) {
            while(!queue.empty()) {
                std::shared_ptr<Hitbox> curr_hitbox = queue.front();
                queue.pop();

                if (hitbox_manager.check_hitbox((inc_piece->get_team() == Color::BLACK) ? Color::WHITE : Color::BLACK, curr_hitbox->get_position()).empty()) {
                    std::optional<std::__1::shared_ptr<Piece>> piece_opt = game_board.get_piece(curr_hitbox->get_position());
                    if (piece_opt.has_value()) {
                        curr_hitbox->highlight();
                    } else {
                        curr_hitbox->show();
                    }
                }
            }
        }
    };

    std::function<void(std::vector<std::queue<std::shared_ptr<Hitbox>>>&)> piece_logic;

    switch (piece) {
        case PIECE::Pawn: piece_logic = pawn_logic; break;
        case PIECE::Bishop:
        case PIECE::Queen:
        case PIECE::Rook: piece_logic = bishop_queen_rook_logic; break;
        case PIECE::Knight: piece_logic = knight_logic; break;
        case PIECE::King: piece_logic = king_logic; break;
        default: return;  // Early return for unexpected cases.
    }

    piece_logic(moves);
}



// void Move_Handler::check_if_im_obstructing(const Position pos, std::shared_ptr<Piece> piece) {
//     // std::vector<std::shared_ptr<Hitbox>> hitboxes = hitbox_manager.check_hitbox(pos);
//     // if (hitboxes.empty()) return;

//     // for (std::shared_ptr<Hitbox> const & hitbox : hitboxes) {
//     //     add_obstructed(pos, hitbox->get_parent());
//     // }
// }

// void Move_Handler::reset_obstructed_at(const Position pos) {    
//     // if (obstructed_pieces_manager.find(pos) == obstructed_pieces_manager.end()) return;

//     // std::vector<std::shared_ptr<Piece>>& obstructed_pieces = obstructed_pieces_manager[pos];

//     // for (const std::shared_ptr<Piece>& obstructing_piece : obstructed_pieces) {
//     //     if (processed_pieces.find(obstructing_piece) != processed_pieces.end()) continue;

//     //     deferred_pieces.push(obstructing_piece);
//     //     processed_pieces.insert(obstructing_piece);
//     // }
//     // obstructed_pieces_manager.erase(pos);
// }

// void Move_Handler::update_deferred_pieces() {
//     // while (!deferred_pieces.empty()) {
//     //     std::shared_ptr<Piece> piece_to_place = deferred_pieces.front();
//     //     deferred_pieces.pop();
//     //     place_piece(piece_to_place);
//     // }
// }

// void Move_Handler::simulate_update() {
//     // std::queue<std::shared_ptr<Piece>> temp_queue = deferred_pieces;

//     // while (!temp_queue.empty()) {
//     //     std::shared_ptr<Piece>  piece_to_place = temp_queue.front();
//     //     temp_queue.pop();
//     //     place_piece(piece_to_place);
//     // }
// }

// void Move_Handler::add_obstructed(const Position pos, std::shared_ptr<Piece> piece) {
//     // obstructed_pieces_manager[pos].emplace_back(piece);
// }

// bool Move_Handler::is_in_squares_between(const Position& pos, Color team) {
//     // for (const std::queue<Position>& queue : squares_between[team]) {
//     //     std::queue<Position> temp = queue;  // Create a copy to iterate through
//     //     while (!temp.empty()) {
//     //         if (temp.front() == pos) return true;
//     //         temp.pop();
//     //     }
//     // }
//     return true;
// }