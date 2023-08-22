#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <map>

#include "constants.hpp"
#include "types.hpp"

#include "hitbox.hpp"

class Piece;

class Board {
public:
    Board(sf::Vector2u window_size); 

    // Board
    void draw_board(sf::RenderWindow& window);

    // Hitboxes
    void make_hitboxes();
    void clear_hitboxes();

    void draw_hitboxes(sf::RenderWindow &window) const;

    // Grid squares
    sf::Vector2f get_size_of_grid_square();
    void set_size_of_grid_square(sf::Vector2f size);

    std::shared_ptr<sf::RectangleShape> get_grid_square_from_map(Position key);
    std::shared_ptr<sf::RectangleShape> get_grid_square_from_map(char row, int col);
    void set_map_of_grid_square(Position key, std::shared_ptr<sf::RectangleShape> val);

    void add_grid();

    void draw_grid(sf::RenderWindow &window);

    // Pieces
    void set_king(std::shared_ptr<Piece> incoming_king);
    std::shared_ptr<Piece> get_king(Color team);

    bool check_piece(Position key);
    bool check_piece(char row, int col);

    std::optional<std::shared_ptr<Piece>> get_piece(char row, int col);
    std::optional<std::shared_ptr<Piece>> get_piece(Position key);
    
    void set_piece(Position key = {}, std::shared_ptr<Piece> piece_to_save = nullptr);
    void set_piece(char row = '\0', int col = 0, std::shared_ptr<Piece> piece_to_save = nullptr);
    void set_piece(std::shared_ptr<Piece> piece_to_save);

    std::optional<Position> check_clicked_hitbox(sf::Vector2i mouse_pos);
    std::optional<std::shared_ptr<Piece>> check_clicked_piece(sf::Vector2i mouse_pos);
    void select_piece(std::shared_ptr<Piece> piece);
    std::shared_ptr<Piece> get_selected_piece();
    
    void draw_piece(sf::RenderWindow &window);

private:
    std::shared_ptr<Piece> king_white;
    std::shared_ptr<Piece> king_black;
    std::shared_ptr<Piece> selected_piece;

    std::unique_ptr<std::map<Position, std::shared_ptr<sf::RectangleShape>>> MAP_OF_GRID;
 
    std::unique_ptr<std::map<Position, std::shared_ptr<Piece>>> PIECES;

    std::vector<std::shared_ptr<Hitbox>> HITBOXES;

    std::unique_ptr<sf::RectangleShape> board;

    sf::Vector2f GRID_SQUARE_SIZE;
};

#endif
