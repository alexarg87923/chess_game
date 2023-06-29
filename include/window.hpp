#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "board.hpp"
#include "pieces/pawn.hpp"
#include "pieces/queen.hpp"
#include "pieces/bishop.hpp"
#include "pieces/king.hpp"
#include "pieces/knight.hpp"
#include "pieces/rook.hpp"

#include <piece.hpp>

class Window {
public:
    Window();
    ~Window();
    void start();

private:
    sf::RenderWindow window;
    std::unique_ptr<Board> game_board;
    sf::Event event;
    
    void listen_left_click(sf::Event& event);

    void handle_drawing();
    void check_close(sf::Event& event);
    void check_select();
    bool check_move();
};

#endif
