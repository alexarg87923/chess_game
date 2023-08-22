#include "board.hpp"

#include "piece.hpp"

sf::Vector2f Board::GRID_SQUARE_SIZE = sf::Vector2f(0, 0);
std::map<Position, sf::RectangleShape> Board::MAP_OF_GRID;
std::map<Position, Piece*> Board::PIECES;
sf::Vector2f Board::MAP_OF_POSITIONS[BOARD_ROW][BOARD_COL];

// bool Board::CHECK_PIECE_FAST[BOARD_ROW][BOARD_COL];
std::map<char, std::map<std::string, Piece*>> Board::MAP_OF_PIECES;

Board::~Board() {}
Board::Board() {}

Board::Board(sf::Vector2u window_size) {
    sf::RectangleShape board_asset;
    sf::Vector2f shape_size = sf::Vector2f(1000, 1000);
    sf::Vector2f half_of_shape = sf::Vector2f(shape_size.x/2, shape_size.y/2);

    board_asset.setSize(shape_size);
    board_asset.setFillColor(sf::Color::White);
    board_asset.setPosition((window_size.x/2) - half_of_shape.x, (window_size.y/2) - half_of_shape.y);

    set_board(board_asset);
    add_grid();
}

void Board::add_grid() {
    sf::Vector2f size = board.getSize();
    sf::Vector2 board_pos = board.getPosition();
    
    size = sf::Vector2f(size.x/BOARD_COL, size.y/BOARD_ROW);

    set_size_of_grid_square(size);

    // Alot happens in this for loop so then I don't have to go through this loop multiple times
    for (int row = 0; row < BOARD_ROW; row++) {
        for (int col = 0; col < BOARD_COL; col++) {
            // A grid piece is made and positioned on its given position on the board
            sf::RectangleShape* grid_piece = new sf::RectangleShape(size);
            sf::Vector2f new_position = sf::Vector2f((row * size.x) + board_pos.x, (col * size.y) + board_pos.y);
            grid_piece->setFillColor(((row + col) % 2 == 0) ? sf::Color::White : sf::Color::Red);
            grid_piece->setPosition(new_position);

            // The SFML coordinate system is turned into the standard chess coordinate system
            char character_offset = ('A' + row);
            std::pair<char, int> key = std::make_pair(character_offset, (BOARD_COL - col));

            // The coordinate is saved to be used as a constant essentially, 
            // And the grid piece is also saved using that new coordinate system
            MAP_OF_POSITIONS[row][col] = new_position;
            set_map_of_grid_square(key, *grid_piece);
        }
    }
}

void Board::draw_grid(sf::RenderWindow &window) {
    for (auto pair : get_map_of_grid_square()) {
        window.draw(pair.second);
    }
}

std::optional<Piece*> Board::check_clicked_piece(sf::Vector2i mouse_pos) {
    for (auto pair : get_map_of_piece()) {
        if(pair.second->get_piece()->getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
            return pair.second;
        }
    }
    return std::nullopt;
}

void Board::select_piece(Piece* piece) {
    selected_piece = piece;
}

Piece* Board::get_selected_piece() {
    return selected_piece;
}

sf::RectangleShape Board::get_board() {
    return board;
}

void Board::set_board(sf::RectangleShape tmp) {
    board = tmp;
}

void Board::set_size_of_grid_square(sf::Vector2f tmp) {
    GRID_SQUARE_SIZE = tmp;
}

sf::Vector2f Board::get_size_of_grid_square() {
    return GRID_SQUARE_SIZE;
}

sf::Vector2f Board::pair_to_pos(char row, int col) {
    return MAP_OF_POSITIONS[row - 'A'][BOARD_COL - col];
}

sf::RectangleShape Board::get_grid_square_from_map(char row, int col) {
    return MAP_OF_GRID[std::make_pair(row, col)];
}

std::map<Position, sf::RectangleShape> Board::get_map_of_grid_square() {
    return MAP_OF_GRID;
}

void Board::set_map_of_grid_square(Position key, sf::RectangleShape val) {
    MAP_OF_GRID[key] = val;
}

std::optional<Piece*> Board::get_piece(char row, int col) {
    auto iter = PIECES.find(std::make_pair(row, col));
    if (iter != PIECES.end()) {
        return iter->second;
    } else {
        return std::nullopt;
    }
}

bool Board::check_piece(char row, int col) {
    auto it = PIECES.find(std::make_pair(row, col));
    return (it != PIECES.end()) ? true : false;
}

// void Board::update_check_piece(char row, int col, bool value) {
//     CHECK_PIECE_FAST[row - 'A'][BOARD_COL - col] = value;
// }

std::optional<Piece*> Board::get_piece(Position key) {
    auto iter = PIECES.find(key);
    if (iter != PIECES.end()) {
        return iter->second;
    } else {
        return std::nullopt;
    }
}

std::map<Position, Piece*> Board::get_map_of_piece() {
    return PIECES;
}

void Board::set_piece(Position key, Piece *val) {
    if (val == nullptr) {
        PIECES.erase(key);
    } else {
        PIECES[key] = val;
    }
}

void Board::draw_piece(sf::RenderWindow &window) {
    for (auto pair : PIECES) {
        if (pair.second) {
            pair.second->draw(window);
        }
    }
}

void Board::save_map_of_pieces(char team, std::string name, Piece* piece) {
    MAP_OF_PIECES[team][name] = piece;
}

Piece* Board::get_piece_from_map(char team, std::string name) {
    return MAP_OF_PIECES[team][name];
}

std::optional<Position> Board::check_clicked_hitbox(sf::Vector2i mouse_pos) {
    for (auto each : HITBOXES) {
        if(each->get_hitbox().getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
            return each->get_position();
        }
    }
    return std::nullopt;
}

void Board::clear_hitboxes() {
    HITBOXES.clear();
}

void Board::make_hitboxes() {
    if (!selected_piece) {
        HITBOXES.clear();
        return;
    }

    HITBOXES = selected_piece->get_hitboxes();
}

void Board::draw_hitboxes(sf::RenderWindow &window) {
    if (!selected_piece) {
        return;
    }

    for (auto each : HITBOXES) {
        window.draw(each->get_hitbox());
    }
}



/*
    OVERLOADED FUNCTIONS
*/

// void Board::update_check_piece(Position key, bool value) {
//     update_check_piece(key.first, key.second, value);
// }

void Board::set_piece(char row, int col, Piece* val) {
    set_piece(std::make_pair(row, col), val);
}

sf::Vector2f Board::pair_to_pos(Position key) {
    return pair_to_pos(key.first, key.second);
}

sf::RectangleShape Board::get_grid_square_from_map(Position key) {
    return get_grid_square_from_map(key.first, key.second);
}

bool Board::check_piece(Position key) {
    return check_piece(key.first, key.second);
}

