#include "move_handler.hpp"

#include "piece.hpp"

Move_Handler::Move_Handler(Board& incoming_game_board) :
    game_board(incoming_game_board), hitbox_manager(game_board)
{}

void Move_Handler::move_piece(std::shared_ptr<Piece> piece, Position pos) {

    auto position = piece->get_pos();

    auto hitboxes = hitbox_manager.check_hitbox(position);

    if(!hitboxes.empty()) {
        for (const auto & hitbox : hitboxes) {
            auto parent = hitbox->get_parent();
            parent->invalidate_moves();
            update_piece(parent);
            place_piece(parent);
        }
    }

    if (obstruction_manager.find(position) != obstruction_manager.end()) {
        auto& obstructed_pieces = obstruction_manager[position];
        for (const auto& obstructed_piece : obstructed_pieces) {
            // Update each obstructing piece
            update_piece(obstructed_piece);
            place_piece(obstructed_piece);
        }
        // Remove this piece from the obstruction manager
        obstruction_manager.erase(position);
    }

    game_board.set_piece(position); // clear the old position of the piece

    piece->set_piece_pos(pos); // set the configuratoin of the piece
    piece->invalidate_moves();

    update_piece(piece);

    place_piece(piece); // place the piece on the state manager
}

void Move_Handler::update_piece(std::shared_ptr<Piece> piece) {
    Piece& p = *piece;

    hitbox_manager.remove_hitboxes_from_state(piece);
    p.clear_hitboxes();
}

void Move_Handler::place_piece(const std::shared_ptr<Piece> piece) {
    Piece& p = *piece;
    auto pos = piece->get_pos();
    
    // Calculate or get cached moves
    std::map<int, std::queue<Position>> moves;
    if (!p.moves_are_valid()) {
        moves = piece->calc_moves(pos);
        p.cache_moves(moves);
    } else {
        moves = p.get_moves();
    }

    game_board.set_piece(piece);

    auto hitboxes = hitbox_manager.check_hitbox(pos);

    if(!hitboxes.empty()) {
        for (const auto & hitbox : hitboxes) {
            auto parent = hitbox->get_parent();
            parent->invalidate_moves();
            update_piece(parent);
            place_piece(parent);
        }
    }

    auto pair = check_for_obstructions_and_valid_moves(piece, moves);
    if (!pair.second.empty()) {
        obstruction_manager[pos] = pair.second;
    }

    hitbox_manager.add_moves_to_state(piece, pair.first);
}

std::pair<std::vector<Position>, std::vector<std::shared_ptr<Piece>>> Move_Handler::check_for_obstructions_and_valid_moves(std::shared_ptr<Piece> inc_piece, std::map<int, std::queue<Position>> moves) {
    std::vector<std::shared_ptr<Piece>> obstructing_pieces;
    std::vector<Position> valid_moves;

    for (auto & pair : moves) {
        while (!pair.second.empty()) {
            Position nextPos = pair.second.front();
            auto pieceOpt = game_board.get_piece(nextPos);
            if (pieceOpt.has_value()) {
                auto piece = pieceOpt.value();
                if (piece->get_team() != inc_piece->get_team()) {
                    valid_moves.push_back(nextPos);
                }
                obstructing_pieces.emplace_back(piece);
                break; // stop checking further in this direction as there's an obstruction
            } else {
                valid_moves.push_back(nextPos);
            }
            pair.second.pop(); // move to the next position in this direction
        }
    }

    return {valid_moves, obstructing_pieces};
}
