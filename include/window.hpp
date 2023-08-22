#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "array_manager.hpp"
#include "board.hpp"

#include "pieces/pawn.hpp"
#include "pieces/queen.hpp"
#include "pieces/bishop.hpp"
#include "pieces/king.hpp"
#include "pieces/knight.hpp"
#include "pieces/rook.hpp"

class Piece;

class Window {
public:
    Window();
    ~Window();
    void start();

    static Array_Manager get_board_hitboxes();

private:
    sf::RenderWindow window;
    std::unique_ptr<Board> game_board;
    sf::Event event;
    static Array_Manager board_hitboxes;

    void listen_left_click(sf::Event& event);

    void handle_drawing();
    void check_close(sf::Event& event);
    void check_select();
    bool check_move();
};

#endif
