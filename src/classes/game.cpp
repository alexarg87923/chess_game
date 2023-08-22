#include "game.hpp"

#include "piece.hpp"

Game::Game() : 
    window(sf::RenderWindow(sf::VideoMode(2560, 1606), "Chesst Game")),
    game_board(Board(window.getSize())),
    board_hitbox_state(State_Manager(game_board)),
    move_handler(game_board, board_hitbox_state)
{}

void Game::start() {
    std::cout << "Starting game...\n";

    game_board.add_grid();

    initialize_pieces();

    // GAME LOOP
    while (window.isOpen()) {
        // handle slowing down of frameRate
        handle_frame_rate(FRAME_RATE, clock);

        // Handles SFML Events
        handle_events();

        // this handles all the drawing of any sprites onto the window
        handle_drawing();
    }
}

void Game::initialize_pieces() {
    auto size_of_grid_square = game_board.get_size_of_grid_square();

    auto white_king = std::make_shared<King>('E', 1, WHITE, size_of_grid_square, move_handler);
    move_handler.place_piece(white_king);
    game_board.set_king(white_king);


    move_handler.place_piece(std::make_shared<Pawn>('A', 1, WHITE, size_of_grid_square, move_handler));

    move_handler.place_piece(std::make_shared<Pawn>('B', 8, BLACK, size_of_grid_square, move_handler));
    move_handler.place_piece(std::make_shared<Pawn>('C', 8, BLACK, size_of_grid_square, move_handler));

    move_handler.place_piece(std::make_shared<Queen>('E', 4, BLACK, size_of_grid_square, move_handler));
    move_handler.place_piece(std::make_shared<Bishop>('B', 5, BLACK, size_of_grid_square, move_handler));

    move_handler.place_piece(std::make_shared<Bishop>('C', 1, WHITE, size_of_grid_square, move_handler));
    move_handler.place_piece(std::make_shared<Rook>('H', 1, WHITE, size_of_grid_square, move_handler));
    move_handler.place_piece(std::make_shared<Knight>('G', 1, WHITE, size_of_grid_square, move_handler));
}

void Game::handle_frame_rate(const float& FRAME_RATE, sf::Clock& clock) {
    sf::Time elapsed = clock.restart();
    if (elapsed.asSeconds() < FRAME_RATE)
    {
        sf::sleep(sf::seconds(FRAME_RATE - elapsed.asSeconds())); 
    }
}

void Game::handle_events() {
    while (window.pollEvent(event)) {

    // Checks to see if window is closed
    check_close(event);

    // When you left click, this function is triggered,
    // it looks to see if you clicked a piece and where the piece is
    listen_left_click(event);
    }
}

void Game::check_close(const sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }
}

void Game::listen_left_click(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            bool moved = handle_move();

            if (!moved) {
                check_select();
            }
        }
    }
}

void Game::check_select() {
    if (!(game_board.get_selected_piece())) {
        auto result = game_board.check_clicked_piece(sf::Mouse::getPosition(window));
        if (result.has_value()) {
            game_board.select_piece(result.value());
        }
    } else {
        game_board.select_piece(nullptr);
    }

    game_board.make_hitboxes();
}

bool Game::handle_move() {
    auto selected_piece = game_board.get_selected_piece();
    if (selected_piece) {
        auto result = game_board.check_clicked_hitbox(sf::Mouse::getPosition(window));

        if (result.has_value()) {
            move_handler.move_piece(selected_piece, result.value());

            game_board.clear_hitboxes();

            game_board.select_piece(nullptr);
            return 1;
        }
    }

    return 0;
}

void Game::handle_drawing() {
    window.clear();

    // draws the game board
    game_board.draw_board(window);

    // draws the grid pieces
    game_board.draw_grid(window);

    // draws every piece on the board (i.e dead pieces arent drawn)
    game_board.draw_piece(window);

    // draws any hitbox in the hitboxes array (empty default)
    game_board.draw_hitboxes(window);

    window.display();
}