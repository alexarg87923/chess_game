#include "move_handler.hpp"

#include "piece.hpp"

Move_Handler::Move_Handler(Board& incoming_game_board, State_Manager& incoming_state_manager) :
    game_board(incoming_game_board),
    state_manager(incoming_state_manager)
{}

void Move_Handler::move_piece(std::shared_ptr<Piece> piece, Position pos) {
    game_board.set_piece(piece->get_pos());

    piece->set_piece_pos(pos);

    update_piece(piece);

    place_piece(piece);
}

bool Move_Handler::is_there_obstruction(Position pos) {
    return (game_board.get_piece(pos).has_value());
}

void Move_Handler::update_piece(std::shared_ptr<Piece> piece) {
    Piece& p = *piece;

    p.clear_valid_moves();
    p.clear_hitboxes();
    p.set_valid_moves(p.get_moves(p.get_pos()));
}

void Move_Handler::place_piece(const std::shared_ptr<Piece> piece) {
    Piece& p = *piece;

    game_board.set_piece(piece);
    auto position = p.get_pos();

    auto hitboxes = state_manager.check_hitbox(position);

    if(!hitboxes.empty()) {
        for (const auto & hitbox : hitboxes) {
            auto parent = hitbox->get_parent();

            state_manager.remove_hitboxes_from_state(parent);
            update_piece(parent);
            state_manager.add_moves_to_state(parent);
        }
    }

    state_manager.add_moves_to_state(piece);
}