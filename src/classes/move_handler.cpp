#include "move_handler.hpp"

#include "piece.hpp"

Move_Handler::Move_Handler(Board& incoming_game_board, State_Manager& incoming_state_manager) :
    game_board(incoming_game_board),
    state_manager(incoming_state_manager)
{}

void Move_Handler::move_piece(std::shared_ptr<Piece> piece, Position pos) {

    if (obstruction_manager.find(piece->get_pos()) != obstruction_manager.end()) {
        auto& obstructed_pieces = obstruction_manager[piece->get_pos()];
        for (const auto& obstructed_piece : obstructed_pieces) {
            // Update each obstructed piece
            update_piece(obstructed_piece);
        }
        // Remove this piece from the obstruction manager
        obstruction_manager.erase(piece->get_pos());
    }

    game_board.set_piece(piece->get_pos()); // clear the old position of the piece

    piece->set_piece_pos(pos); // set the configuratoin of the piece

    update_piece(piece); // update the configuration of the piece

    place_piece(piece); // place the piece on the state manager
}

bool Move_Handler::is_there_obstruction(Position pos) {
    return game_board.get_piece(pos).has_value();
}

void Move_Handler::update_piece(std::shared_ptr<Piece> piece) {
    Piece& p = *piece;

    p.clear_valid_moves();
    state_manager.remove_hitboxes_from_state(piece);
    p.clear_hitboxes();
    p.set_valid_moves(p.get_moves(p.get_pos()));
}

void Move_Handler::place_piece(const std::shared_ptr<Piece> piece) {
    Piece& p = *piece;

    game_board.set_piece(piece);

    state_manager.add_moves_to_state(piece);

    auto newly_obstructed_pieces = check_for_obstructions(piece);
    if (!newly_obstructed_pieces.empty()) {
        obstruction_manager[piece->get_pos()] = newly_obstructed_pieces;
    }
}

std::vector<std::shared_ptr<Piece>> Move_Handler::check_for_obstructions(std::shared_ptr<Piece> piece) {
    std::vector<std::shared_ptr<Piece>> obstructedPieces;

    // Here, you'll need to implement the logic to check for pieces that are obstructed 
    // by the piece passed as an argument. This might involve scanning the board in 
    // each direction from the piece's position until you hit another piece or the 
    // edge of the board.

    return obstructedPieces;
}

// void Move_Handler::reset_parents_at(const Position pos) {
//     auto hitboxes = state_manager.check_hitbox(pos);

//     if(!hitboxes.empty()) {
//         for (const auto & hitbox : hitboxes) {
//             auto parent = hitbox->get_parent();

//             state_manager.remove_hitboxes_from_state(parent);
//             update_piece(parent);
//             state_manager.add_moves_to_state(parent);
//         }
//     }
// }