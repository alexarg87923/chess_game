#include "move_handler.hpp"

#include "piece.hpp"

Move_Handler::Move_Handler(Board& incoming_game_board) :
    game_board(incoming_game_board), hitbox_manager(game_board)
{}

void Move_Handler::move_piece(std::shared_ptr<Piece> piece, Position pos) {
    auto position = piece->get_pos();

    game_board.set_piece(position, nullptr); // clear the old position of the piece

    reset_obstructed_at(position);

    piece->set_piece_pos(pos); // set the configuratoin of the piece

    piece->invalidate_moves();

    place_piece(piece); // place the piece on the state manager
}

void Move_Handler::reset_hitboxes(std::shared_ptr<Piece> piece) {
    Piece& p = *piece;

    hitbox_manager.remove_hitboxes_from_state(piece);
    p.clear_hitboxes();
}

void Move_Handler::place_piece(const std::shared_ptr<Piece> piece) {
    Piece& p = *piece;
    auto pos = p.get_pos();

    reset_hitboxes(piece);

    std::map<int, std::__1::queue<Position>> moves;

    if (p.moves_are_valid()) {
        moves = p.get_moves();
    } else {
        moves = p.calc_moves(pos);
        p.cache_moves(moves);
    }

    game_board.set_piece(pos, piece);

    check_if_im_obstructing(pos, piece);
    
    reset_obstructed_at(pos);

    auto pair = check_for_obstructions_and_valid_moves(piece, moves);

    hitbox_manager.add_moves_to_state(piece, pair.first);

    while (!deferred_pieces.empty()) {
        auto piece_to_place = deferred_pieces.front();
        deferred_pieces.pop();
        place_piece(piece_to_place);
    }

    processed_pieces.clear();
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
                add_obstructed(nextPos, inc_piece);
                break; // stop checking further in this direction as there's an obstruction
            } else {
                valid_moves.push_back(nextPos);
            }
            pair.second.pop(); // move to the next position in this direction
        }
    }

    return {valid_moves, obstructing_pieces};
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
        // add_obstruction(pos, piece);
        for (auto const & hitbox : hitboxes) {
            add_obstructed(pos, hitbox->get_parent());
        }
    }
}

void Move_Handler::add_obstructed(const Position pos, std::shared_ptr<Piece> piece) {
    obstructed_pieces_manager[pos].emplace_back(piece);
}