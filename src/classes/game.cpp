#include "game.hpp"

#include "piece.hpp"

Game::Game() : window(new sf::RenderWindow(sf::VideoMode(2560, 1606), "Chesst Game")), game_board(new Board(window->getSize())), board_hitbox_state(new State_Manager(game_board)) {}
Game::~Game() {}

void Game::start() {
    std::cout << "Starting game...\n";

    game_board->add_grid();

    initialize_pieces();

    // GAME LOOP
    while (window->isOpen()) {
        // handle slowing down of frameRate
        handle_frame_rate(FRAME_RATE, clock);

        // Handles SFML Events
        handle_events();

        // this handles all the drawing of any sprites onto the window
        handle_drawing();
    }
}

void Game::initialize_pieces() const {
    auto size_of_grid_square = game_board->get_size_of_grid_square();
    
    game_board->set_piece(new Pawn('A', 1, WHITE, size_of_grid_square));

    game_board->set_piece(new Pawn('B', 8, BLACK, size_of_grid_square));
    game_board->set_piece(new Pawn('C', 8, BLACK, size_of_grid_square));

    game_board->set_piece(new Queen('E', 4, BLACK, size_of_grid_square));
    game_board->set_piece(new Bishop('B', 5, BLACK, size_of_grid_square));

    game_board->set_piece(new Bishop('C', 1, WHITE, size_of_grid_square));
    game_board->set_piece(new Rook('H', 1, WHITE, size_of_grid_square));
    game_board->set_piece(new Knight('G', 1, WHITE, size_of_grid_square));
    game_board->set_piece(new King('E', 1, WHITE, size_of_grid_square));
}

void Game::handle_frame_rate(const float& FRAME_RATE, sf::Clock& clock) {
    sf::Time elapsed = clock.restart();
    if (elapsed.asSeconds() < FRAME_RATE)
    {
        sf::sleep(sf::seconds(FRAME_RATE - elapsed.asSeconds())); 
    }
}

void Game::handle_events() {
    while (window->pollEvent(event)) {

    // Checks to see if window is closed
    check_close(event);

    // When you left click, this function is triggered,
    // it looks to see if you clicked a piece and where the piece is
    listen_left_click(event);
    }
}

void Game::check_close(const sf::Event& event) const {
    if (event.type == sf::Event::Closed) {
        window->close();
    }
}

void Game::listen_left_click(const sf::Event& event) const{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            bool moved = check_move();

            if (!moved) {
                check_select();
            }
        }
    }
}

void Game::check_select() const {
    if (!(game_board->get_selected_piece())) {
        auto result = game_board->check_clicked_piece(sf::Mouse::getPosition(*window));
        if (result.has_value()) {
            game_board->select_piece(result.value());
        }
    } else {
        game_board->select_piece(nullptr);
    }

    game_board->make_hitboxes();
}

bool Game::check_move() const {
    Piece* selected_piece = game_board->get_selected_piece();
    if (selected_piece) {
        auto result = game_board->check_clicked_hitbox(sf::Mouse::getPosition(*window));

        if (result.has_value()) {
            selected_piece->update_position(result.value());

            board_hitbox_state->refresh_hitbox_state(selected_piece);

            game_board->select_piece(nullptr);
            game_board->clear_hitboxes();

            return 1;
        }
    }

    return 0;
}

void Game::handle_drawing() const {
    window->clear();

    // draws the game board
    window->draw(*game_board->get_board());

    // draws the grid pieces
    game_board->draw_grid(*window);

    // draws every piece on the board (i.e dead pieces arent drawn)
    game_board->draw_piece(*window);

    // draws any hitbox in the hitboxes array (empty default)
    game_board->draw_hitboxes(*window);

    window->display();
}