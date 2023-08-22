#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "constant.hpp"
#include <iostream>
#include <map>
#include <piece.hpp>

// using PieceNameToHitboxPosition = std::unordered_map<std::string, std::vector<Position>>;
// using TeamToPieceMap = std::unordered_map<char, PieceNameToHitboxPosition>;

class Board {
public:
    Board();
    ~Board();
    Board(sf::Vector2u window_size); 

    sf::RectangleShape get_board();
    void set_board(sf::RectangleShape tmp);

    void draw_grid(sf::RenderWindow &window);
    void draw_hitboxes(sf::RenderWindow &window);

    std::optional<Position> check_clicked_hitbox(sf::Vector2i mouse_pos);
    std::optional<Piece*> check_clicked_piece(sf::Vector2i mouse_pos);
    void select_piece(Piece* piece);
    Piece* get_selected_piece();
    void make_hitboxes();
    void clear_hitboxes();
    void refresh_valid_moves();

    static void refresh_check_hitbox();
    static void update_check_hitbox(char team, char row, int col, bool value);
    static sf::Vector2f get_size_of_grid_square();
    static void set_size_of_grid_square(sf::Vector2f tmp);

    static sf::Vector2f pair_to_pos(Position key);
    static sf::Vector2f pair_to_pos(char row, int col);

    static Piece* get_king(char team);
    static bool check_hitbox(char team, Position key);
    static bool check_hitbox(char team, char row, int col);
    static bool check_piece(Position key);
    static bool check_piece(char row, int col);
    static void update_check_piece(Position key, bool value);
    static void update_check_piece(char row, int col, bool value);

    // static std::vector<Position>& get_piece_hitboxes(char &team, std::string &name);
    // static void save_piece_hitboxes(char &team, std::string &name, std::vector<Position> valid_moves);

    static sf::RectangleShape get_grid_square_from_map(Position key);
    static sf::RectangleShape get_grid_square_from_map(char row, int col);
    static std::map<Position, sf::RectangleShape> get_map_of_grid_square();
    static void set_map_of_grid_square(Position key, sf::RectangleShape val);

    static std::optional<Piece*> get_piece(char row, int col);
    static std::optional<Piece*> get_piece(Position key);
    static std::map<Position, Piece*> get_map_of_piece();
    static void set_piece(Position key, Piece* val);
    static void set_piece(char row, int col, Piece* val);

    static void save_map_of_pieces(char team, std::string name, Piece* piece);
    static Piece* get_piece_from_map(char team, std::string name);
    static void draw_piece(sf::RenderWindow &window);

private:
    static sf::Vector2f GRID_SQUARE_SIZE;
    static std::map<Position, sf::RectangleShape> MAP_OF_GRID;
    static std::map<Position, Piece*> PIECES;
    static std::map<char, std::map<std::string, Piece*>> MAP_OF_PIECES;
    static bool CHECK_PIECE_FAST[BOARD_ROW][BOARD_COL];
    static std::unordered_map<char, bool[BOARD_ROW][BOARD_COL]> CHECK_HITBOX_FAST;
    
    std::map<Position, sf::RectangleShape*> HITBOXES;
    

    static sf::Vector2f MAP_OF_POSITIONS[BOARD_ROW][BOARD_COL];
    Piece* selected_piece = nullptr;

    static void clear_check_hitbox();


    sf::RectangleShape board;
    void add_grid();
};

#endif
