#include "window.hpp"
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<Window> game = std::make_unique<Window>();

    game->start();

    return 0;
}