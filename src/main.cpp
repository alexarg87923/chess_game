#include "game.hpp"
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<Game> game = std::make_unique<Game>();

    game->start();

    return 0;
}