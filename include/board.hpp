#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <map>

#include "constant.hpp"
#include "types.hpp"

#include "hitbox.hpp"

class Piece;

class Board {
public:
    Board();
    ~Board();
    Board(sf::Vector2u window_size); 

    // Board
    sf::RectangleShape* get_board();
    void set_board(sf::RectangleShape* incoming_board);

    // Hitboxes
    void make_hitboxes();
    void clear_hitboxes();

    void draw_hitboxes(sf::RenderWindow &window) const;

    // Grid squares
    sf::Vector2f get_size_of_grid_square();
    void set_size_of_grid_square(sf::Vector2f tmp);

    sf::RectangleShape* get_grid_square_from_map(Position key);
    sf::RectangleShape* get_grid_square_from_map(char row, int col);
    void set_map_of_grid_square(Position key, sf::RectangleShape val);

    void add_grid();

    void draw_grid(sf::RenderWindow &window);

    // Pieces
    void set_king(Piece* incoming_king);
    Piece* get_king(Color team);

    bool check_piece(Position key);
    bool check_piece(char row, int col);

    std::optional<Piece*> get_piece(char row, int col);
    std::optional<Piece*> get_piece(Position key);
    
    void set_piece(Position key = {}, Piece* piece_to_save = nullptr);
    void set_piece(char row = '\0', int col = 0, Piece* piece_to_save = nullptr);
    void set_piece(Piece* piece_to_save);

    std::optional<Position> check_clicked_hitbox(sf::Vector2i mouse_pos);
    std::optional<Piece*> check_clicked_piece(sf::Vector2i mouse_pos);
    void select_piece(Piece* piece);
    Piece* get_selected_piece();
    
    void draw_piece(sf::RenderWindow &window);

private:
    Piece* king_white;
    Piece* king_black;
    Piece* selected_piece;

    sf::Vector2f GRID_SQUARE_SIZE;

    std::map<Position, sf::RectangleShape*> *MAP_OF_GRID;
 
    std::map<Position, Piece*> *PIECES;

    std::vector<Hitbox*> HITBOXES;

    sf::RectangleShape *board;
};

#endif
