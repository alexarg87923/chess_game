#pragma once

#include "piece.hpp"

class Knight : public Piece {
public:
    Knight();
    ~Knight();

    Knight(char row, int col, Color team_color, sf::Vector2f size);
    Knight(const Position &pos, Color team_color, sf::Vector2f size);

    std::vector<std::queue<std::shared_ptr<Hitbox>>> calc_moves(const Position& pos) override;
};

