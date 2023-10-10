#pragma once

#include "piece.hpp"

class King : public Piece {
public:
    King();
    ~King();

    King(char row, int col, Color team_color, sf::Vector2f size);
    King(const Position& pos, Color team_color, sf::Vector2f size);

    std::vector<std::queue<std::shared_ptr<Hitbox>>> calc_moves(const Position& pos) override;

private:
    bool already_moved = false;
};


