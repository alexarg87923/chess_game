#include "board.hpp"

#include "piece.hpp"

Board::Board(sf::Vector2u window_size) : 
    king_white(nullptr), king_black(nullptr), selected_piece(nullptr),
    MAP_OF_GRID(std::make_unique<std::map<Position, std::shared_ptr<sf::RectangleShape>>>()), PIECES(std::make_unique<std::map<Position, std::shared_ptr<Piece>>>()),
    HITBOXES(), board(nullptr)
{
    auto board_asset = std::make_unique<sf::RectangleShape>();
    sf::Vector2f shape_size = sf::Vector2f(1000, 1000);
    sf::Vector2f half_of_shape = sf::Vector2f(shape_size.x/2, shape_size.y/2);

    board_asset->setSize(shape_size);
    board_asset->setFillColor(sf::Color::White);
    board_asset->setPosition((window_size.x/2) - half_of_shape.x, (window_size.y/2) - half_of_shape.y);

    board = std::move(board_asset);
}

void Board::add_grid() {
    sf::Vector2f size = board->getSize();
    sf::Vector2 board_pos = board->getPosition();
    
    size = sf::Vector2f(size.x/BOARD_COL, size.y/BOARD_ROW);

    set_size_of_grid_square(size);

    // Alot happens in this for loop so then I don't have to go through this loop multiple times
    for (int row = 0; row < BOARD_ROW; row++) {
        for (int col = 0; col < BOARD_COL; col++) {
            // A grid piece is made and positioned on its given position on the board
            auto grid_piece = std::make_shared<sf::RectangleShape>(size);
            sf::Vector2f new_position = sf::Vector2f((row * size.x) + board_pos.x, (col * size.y) + board_pos.y);

            grid_piece->setFillColor(((row + col) % 2 == 0) ? sf::Color::White : sf::Color::Red);
            grid_piece->setPosition(new_position);

            // The SFML coordinate system is turned into the standard chess coordinate system
            char character_offset = ('A' + row);
            Position key = {character_offset, (BOARD_COL - col)};

            set_map_of_grid_square(key, grid_piece);
        }
    }
}

void Board::draw_grid(sf::RenderWindow &window) {
    for (auto pair : *MAP_OF_GRID) {
        window.draw(*pair.second);
    }
}

std::shared_ptr<Piece> Board::get_king(Color team) {
    return (team == WHITE) ? king_white : king_black;
}

void Board::set_king(std::shared_ptr<Piece> incoming_king) {
    if(incoming_king->get_team() == WHITE) {
        king_white = incoming_king;
    } else {
        king_black = incoming_king;
    }
}

std::optional<std::shared_ptr<Piece>> Board::check_clicked_piece(sf::Vector2i mouse_pos) {
    for (auto pair : *PIECES) {
        if(pair.second->get_piece()->getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
            return pair.second;
        }
    }
    return std::nullopt;
}

void Board::select_piece(std::shared_ptr<Piece> piece) {
    selected_piece = piece;
}

std::shared_ptr<Piece> Board::get_selected_piece() {
    return selected_piece;
}

void Board::draw_board(sf::RenderWindow& window) {
    window.draw(*board);
}

void Board::set_size_of_grid_square(sf::Vector2f tmp) {
    GRID_SQUARE_SIZE = tmp;
}

sf::Vector2f Board::get_size_of_grid_square() {
    return GRID_SQUARE_SIZE;
}

std::shared_ptr<sf::RectangleShape> Board::get_grid_square_from_map(char row, int col) {
    return (*MAP_OF_GRID)[Position{row, col}];
}

void Board::set_map_of_grid_square(Position key, std::shared_ptr<sf::RectangleShape> val) {
    (*MAP_OF_GRID)[key] = val;
}

std::optional<std::shared_ptr<Piece>> Board::get_piece(char row, int col) {
    auto iter = PIECES->find({row, col});
    if (iter != PIECES->end()) {
        return iter->second;
    } else {
        return std::nullopt;
    }
}

bool Board::check_piece(char row, int col) {
    auto it = PIECES->find({row, col});
    return (it != PIECES->end()) ? true : false;
}

std::optional<std::shared_ptr<Piece>> Board::get_piece(Position key) {
    auto iter = PIECES->find(key);
    if (iter != PIECES->end()) {
        return iter->second;
    } else {
        return std::nullopt;
    }
}

void Board::set_piece(Position key, std::shared_ptr<Piece> val) {
    if (val == nullptr) {
        PIECES->erase(key);
    } else if (key == Position{}) {
        auto position = val->get_pos();
        (*PIECES)[position] = val;
        val->set_position((*MAP_OF_GRID)[position]->getPosition());
    } else {
        (*PIECES)[key] = val;
         val->set_position((*MAP_OF_GRID)[key]->getPosition());
    }
}

void Board::draw_piece(sf::RenderWindow &window) {
    for (auto pair : (*PIECES)) {
        if (pair.second) {
            pair.second->draw(window);
        }
    }
}

std::optional<Position> Board::check_clicked_hitbox(sf::Vector2i mouse_pos) {
    for (auto each : HITBOXES) {
        if(each->get_hitbox()->getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
            return each->get_position();
        }
    }
    return std::nullopt;
}

void Board::clear_hitboxes() {
    HITBOXES.clear();
}

void Board::get_hitboxes_from_piece() {
    HITBOXES = selected_piece->get_hitboxes();
}

void Board::draw_hitboxes(sf::RenderWindow &window) const {
    if (!selected_piece) {
        return;
    }

    for (auto each : HITBOXES) {
        window.draw(*each->get_hitbox());
    }
}



/*
    OVERLOADED FUNCTIONS
*/


void Board::set_piece(char row, int col, std::shared_ptr<Piece> piece_to_save) {
    set_piece({row, col}, piece_to_save);
}

void Board::set_piece(std::shared_ptr<Piece> piece_to_save) {
    set_piece({}, piece_to_save);
}

std::shared_ptr<sf::RectangleShape> Board::get_grid_square_from_map(Position key) {
    return get_grid_square_from_map(key.row, key.col);
}

bool Board::check_piece(Position key) {
    return check_piece(key.row, key.col);
}

