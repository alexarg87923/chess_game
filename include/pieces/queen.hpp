#pragma once

#include "pieces/bishop.hpp"
#include "pieces/rook.hpp"

class Queen : public Rook, public Bishop {
public:
    Queen();
    ~Queen();

    Queen(char row, int col, Color team_color, sf::Vector2f size);
    Queen(const Position& pos, Color team_color, sf::Vector2f size);

    std::vector<std::queue<std::shared_ptr<Hitbox>>> calc_moves(const Position& pos) override;
};