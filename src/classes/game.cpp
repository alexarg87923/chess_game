#include "game.hpp"

#include "piece.hpp"

State_Manager Game::board_hitbox_state;

Game::Game() : window(sf::VideoMode(2560, 1606), "Chesst Game"), game_board(std::make_unique<Board>(window.getSize())) {}
Game::~Game() {}

void Game::start() {
    std::cout << "Starting game...\n";
    
    Pawn testPawn = Pawn('A', 1, 'w');

    Pawn enemyPawn = Pawn('B', 8, 'b');
    Pawn enemyPawn2 = Pawn('C', 8, 'b');

    Queen testQueen = Queen('E', 4, 'b');
    Bishop enemyBishop = Bishop('B', 5, 'b');

    Bishop testBishop = Bishop('C', 1, 'w');
    Rook testRook = Rook('H', 1, 'w');
    Knight testKnight = Knight('G', 1, 'w');
    King testKing = King('E', 1, 'w');

    // GAME LOOP
    while (window.isOpen()) {

        while (window.pollEvent(event)) {
            // Checks to see if window is closed
            check_close(event);

            // When you left click, this function is triggered,
            // it looks to see if you clicked a piece and where the piece is
            listen_left_click(event);
        }

        // this handles all the drawing of any sprites onto the window
        handle_drawing();
    }
}

void Game::check_close(sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }
}

void Game::listen_left_click(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            bool moved = check_move();

            if (!moved) {
                check_select();
            }
        }
    }
}

void Game::check_select() {
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

bool Game::check_move() {
    Piece* selected_piece = game_board->get_selected_piece();
    if (selected_piece) {
        auto result = game_board->check_clicked_hitbox(sf::Mouse::getPosition(window));

        if (result.has_value()) {
            selected_piece->update_position(result.value());

            board_hitbox_state.refresh_hitbox_state(selected_piece);

            game_board->select_piece(nullptr);
            game_board->clear_hitboxes();
            
            return 1;
        }
    }

    return 0;
}

void Game::handle_drawing() {
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

State_Manager Game::get_hitbox_states() {
    return board_hitbox_state;
}
