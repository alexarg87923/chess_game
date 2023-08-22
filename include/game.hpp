#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Sleep.hpp>

#include "state_manager.hpp"
#include "board.hpp"

#include "pieces/pawn.hpp"
#include "pieces/queen.hpp"
#include "pieces/bishop.hpp"
#include "pieces/king.hpp"
#include "pieces/knight.hpp"
#include "pieces/rook.hpp"

class Piece;

class Game {
public:
    Game();
    ~Game();
    void start();

    static State_Manager *get_hitbox_states();

private:
    sf::RenderWindow window;
    std::unique_ptr<Board> game_board;
    sf::Event event;
    
    static State_Manager *board_hitbox_state;

    void listen_left_click(sf::Event& event);

    void handle_drawing();
    void check_close(sf::Event& event);
    void check_select();
    bool check_move();
};

#endif
