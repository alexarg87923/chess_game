#include "window.hpp"

Window::Window() : window(sf::VideoMode(2560, 1606), "Chesst Game") {}
Window::~Window() {}

void Window::start() {
    game_board = std::make_unique<Board>(window.getSize());

    std::cout << "Starting game...\n";

    Pawn testPawn = Pawn('A', 1, 'w');

    Pawn enemyPawn = Pawn('B', 8, 'b');
    Queen testQueen = Queen('E', 4, 'b');
    Bishop enemyBishop = Bishop('B', 5, 'b');

    Bishop testBishop = Bishop('C', 1, 'w');
    Rook testRook = Rook('H', 1, 'w');
    Knight testKnight = Knight('G', 1, 'w');
    King testKing = King('E', 1, 'w');

    /* 
      Since order of pieces matters when initializing, then I refresh after I create them all
      This is because if I spawn a king, then spawn an enemy queen which would cover some of the king's squares
      The king will not refresh his moves
      I could make it so there's a refresh after every piece is initialized but refreshing is costly to do every frame even though nothing has happened
      So I only do it when a piece is actualled moved
    */
    game_board->refresh_check_hitbox();
    game_board->refresh_valid_moves();

    // GAME LOOP
    while (window.isOpen()) {

        while (window.pollEvent(event)) {
            // Checks to see if window is closed
            check_close(event);

            // When you left click, this function is triggered,
            // it looks to see if you clicked a piece and where
            listen_left_click(event);
        }

        // this handles all the drawing of any sprites onto the window
        handle_drawing();
    }
}

void Window::check_close(sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }
}

void Window::listen_left_click(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            bool moved = check_move();

            if (!moved) {
                check_select();
            }
        }
    }
}

void Window::check_select() {
    if (!(game_board->get_selected_piece())) {
        auto result = game_board->check_clicked_piece(sf::Mouse::getPosition(window));
        if (result.has_value()) {
            game_board->select_piece(result.value());
        }
    } else {
        game_board->select_piece(nullptr);
    }

    game_board->make_hitboxes();
}

bool Window::check_move() {
    if ((game_board->get_selected_piece())) {
        auto result = game_board->check_clicked_hitbox(sf::Mouse::getPosition(window));
        if (result.has_value()) {
            game_board->get_selected_piece()->update_position(result.value());

            game_board->select_piece(nullptr);
            game_board->clear_hitboxes();

            game_board->refresh_check_hitbox();
            game_board->refresh_valid_moves();


            return 1;
        }
    }

    return 0;
}

void Window::handle_drawing() {
    window.clear();

    // draws the game board
    window.draw(game_board->get_board());
    // draws the grid pieces
    game_board->draw_grid(window);
    // draws every piece on the board (i.e dead pieces arent drawn)
    Board::draw_piece(window);
    // draws any hitbox in the hitboxes array (empty default)
    game_board->draw_hitboxes(window);

    window.display();
}