#pragma once

#include "piece.hpp"

class Rook : virtual public Piece {
public:
    Rook();
    ~Rook();

    Rook(char row, int col, Color team_color, sf::Vector2f size);
    Rook(const Position& pos, Color team_color, sf::Vector2f size);

    virtual std::vector<std::queue<std::shared_ptr<Hitbox>>> calc_moves(const Position& pos);
};
