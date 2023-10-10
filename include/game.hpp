#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Sleep.hpp>

#include "move_handler.hpp"
#include "hitbox_manager.hpp"
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
    void start();

private:
    sf::Event event;
    sf::Clock clock;

    sf::RenderWindow window;
    Board game_board;
    // Hitbox_Manager board_hitbox_state;
    Move_Handler move_handler;

    const float FRAME_RATE = 1.0f / 30.0f;

    void handle_events();
    void handle_frame_rate(const float& frameRate, sf::Clock& clock);
    void initialize_game();
    void initialize_pieces();
    void listen_left_click(const sf::Event& event);
    void handle_drawing();

    void check_close(const sf::Event& event);
};

