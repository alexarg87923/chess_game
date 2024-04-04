#include "move_handler.hpp"

Move_Handler::Move_Handler(Board& incoming_game_board) :
    game_board(incoming_game_board), hitbox_manager(game_board)
{}

void Move_Handler::move_piece(std::shared_ptr<Piece> piece, Position pos) {
    Position position = piece->get_pos();

    LOG(INFO) << "Updating position....";
    game_board.clear_position(position);
    piece->set_piece_pos(pos);

    LOG(INFO) << "Resetting obstructed pieces at piece->old_position";
    reset_obstructed_at(position);

    LOG(INFO) << "Invalidating cache...";
    piece->invalidate_moves();

    LOG(INFO) << "Adding Piece to be processed...";
    re_process_list.push_back(piece);

    LOG(INFO) << "\n\n========Placing piece========\n\n";
    place_piece(piece);
}

void Move_Handler::reset_hitboxes(std::shared_ptr<Piece> piece) {
    Piece& p = *piece;

    hitbox_manager.remove_hitboxes_from_state(piece);
    p.clear_hitboxes();
}

void Move_Handler::place_piece(std::shared_ptr<Piece> piece) {
    Piece& p = *piece;
    Position pos = p.get_pos();
    
    LOG(INFO) << "Adding Piece to be processed...";
    re_process_list.push_back(piece);

    LOG(INFO) << "Reseting Piece Hitboxes...";
    reset_hitboxes(piece);

    LOG(INFO) << "Checking Cache...";
    std::vector<std::queue<std::shared_ptr<Hitbox>>> all_hitboxes = check_cache_or_calculate(pos, piece);

    LOG(INFO) << "Adding Hitboxes to Hitbox Manager...";
    hitbox_manager.add_moves_to_state(piece, all_hitboxes);

    LOG(INFO) << "Processing all pieces that were affected";
    process_list();
}

std::vector<std::queue<std::shared_ptr<Hitbox>>> Move_Handler::check_cache_or_calculate(Position pos, std::shared_ptr<Piece>& piece) {
    Piece& p = *piece;

    if (p.hitboxes_are_valid()) {
        // LOG(INFO) << "Cache hit...";
        return p.get_cache();
    } else {
        // LOG(INFO) << "Cache miss, Calculating...";
        std::vector<std::queue<std::shared_ptr<Hitbox>>> all_moves = p.calc_moves(pos);
        p.cache_moves(all_moves);
        game_board.set_piece(pos, piece);
        check_if_im_obstructing(pos);
        return all_moves;
    }
}

void Move_Handler::check_for_obstructions_and_valid_moves(std::shared_ptr<Piece> inc_piece, std::vector<std::queue<std::shared_ptr<Hitbox>>> moves) {
    PIECE piece = inc_piece->get_piece_type();
    auto pawn_logic = [inc_piece, this](std::vector<std::queue<std::shared_ptr<Hitbox>>>& moves) {
        auto processMoves = [inc_piece, this](std::queue<std::shared_ptr<Hitbox>>& queue, bool isDiagonal) {
            Color team = inc_piece->get_team();
            bool continueChecking = true;

            while (!queue.empty() && continueChecking) {
                std::shared_ptr<Hitbox> curr_hitbox = queue.front();
                queue.pop();
                curr_hitbox->unhighlight();

                std::optional<std::shared_ptr<Piece>> piece_opt = game_board.get_piece(curr_hitbox->get_position());
                if (isDiagonal) {
                    if (piece_opt.has_value()) {
                        re_process_list.emplace_back(piece_opt.value());
                        curr_hitbox->show();
                        curr_hitbox->highlight();
                    }
                } else {
                    if (!piece_opt.has_value()) {
                        re_process_list.emplace_back(piece_opt.value());
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
    
    auto bishop_queen_rook_logic = [inc_piece, this](std::vector<std::queue<std::shared_ptr<Hitbox>>>& moves) {
        Color team = inc_piece->get_team();

        for (auto& queue : moves) {
            while(!queue.empty()) {
                Hitbox& curr_hitbox = *queue.front();
                queue.pop();
                curr_hitbox.unhighlight();

                std::optional<std::__1::shared_ptr<Piece>> piece_opt = game_board.get_piece(curr_hitbox.get_position());
                if (piece_opt.has_value()) {
                    auto piece = piece_opt.value();

                    re_process_list.emplace_back(piece);
                    if (piece->get_team() != team) {
                        curr_hitbox.show();
                        curr_hitbox.highlight();
                    } else {
                        curr_hitbox.hide();
                    }
                    break;
                }

                curr_hitbox.show();
            }
        }
    };

    auto knight_logic = [this, inc_piece](std::vector<std::queue<std::shared_ptr<Hitbox>>>& moves) {
        Color team = inc_piece->get_team();

        for (auto& queue : moves) {
            while(!queue.empty()) {
                std::shared_ptr<Hitbox> curr_hitbox = queue.front();
                queue.pop();
                curr_hitbox->unhighlight();
                std::optional<std::__1::shared_ptr<Piece>> piece_opt = game_board.get_piece(curr_hitbox->get_position());
                if (piece_opt.has_value()) {
                    re_process_list.emplace_back(piece_opt.value());
                    if (piece_opt.value()->get_team() != team) {
                        curr_hitbox->show();
                        curr_hitbox->highlight();
                    } else {
                        curr_hitbox->hide();
                    }
                }
                curr_hitbox->show();
            }
        }
    };

    auto king_logic = [this, inc_piece](std::vector<std::queue<std::shared_ptr<Hitbox>>>& moves) {
        Color team = inc_piece->get_team();

        for (auto& queue : moves) {
            if (queue.empty()) continue;
 
            while(!queue.empty()) {
                std::shared_ptr<Hitbox> curr_hitbox = queue.front();
                queue.pop();
                curr_hitbox->unhighlight();

                if (hitbox_manager.check_hitbox((team == Color::BLACK) ? Color::WHITE : Color::BLACK, curr_hitbox->get_position()).empty()) {
                    std::optional<std::__1::shared_ptr<Piece>> piece_opt = game_board.get_piece(curr_hitbox->get_position());
                    if (piece_opt.has_value()) {
                        re_process_list.emplace_back(piece_opt.value());
                        if (piece_opt.value()->get_team() != team) {
                            curr_hitbox->show();
                            curr_hitbox->highlight();
                        } else {
                            curr_hitbox->hide();
                        }
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



void Move_Handler::check_if_im_obstructing(const Position pos) {
    std::vector<std::shared_ptr<Hitbox>> hitboxes = hitbox_manager.check_hitbox(pos);
    if (hitboxes.empty()) return;

    for (std::shared_ptr<Hitbox> const & hitbox : hitboxes) {
        obstructed_pieces_manager[pos].emplace_back(hitbox->get_parent());
        re_process_list.emplace_back(hitbox->get_parent());
    }
}

void Move_Handler::reset_obstructed_at(Position pos) {    
    if (obstructed_pieces_manager.find(pos) == obstructed_pieces_manager.end()) return;

    std::vector<std::shared_ptr<Piece>>& obstructed_pieces = obstructed_pieces_manager[pos];

    while(!obstructed_pieces.empty()) {
        auto piece = obstructed_pieces.back();
        obstructed_pieces.pop_back();
        re_process_list.push_back(piece);
    }
}

void Move_Handler::process_list() {    
    if (re_process_list.empty()) return;

    for (std::shared_ptr<Piece>& piece_to_process : re_process_list) {
        // obstructed_pieces_manager[pos].emplace_back(piece_to_process);

        for (auto hitbox : piece_to_process->get_hitboxes_mutable()) {
            hitbox->hide();
        }

		LOG(INFO) << "count is: " << piece_to_process.use_count() << " for " << piece_to_process->get_name() << std::endl;

        check_for_obstructions_and_valid_moves(piece_to_process, piece_to_process->get_cache());

		LOG(INFO) << "count is: " << piece_to_process.use_count() << " for " << piece_to_process->get_name() << std::endl;
    }

}