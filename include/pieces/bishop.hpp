#pragma once

#include "piece.hpp"

class Bishop : virtual public Piece {
public:
    Bishop();
    ~Bishop();

    Bishop(char row, int col, Color team_color, sf::Vector2f size);
    Bishop(const Position& pos, Color team_color, sf::Vector2f size);

    virtual std::vector<std::queue<std::shared_ptr<Hitbox>>> calc_moves(const Position& pos) override;
};

