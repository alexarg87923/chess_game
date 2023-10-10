#pragma once

#include "piece.hpp"

class Pawn : public Piece {
public:
    Pawn();
    ~Pawn();

    Pawn(char row, int col, Color team_color, sf::Vector2f size);
    Pawn(const Position& pos, Color team_color, sf::Vector2f size);

    std::vector<std::queue<std::shared_ptr<Hitbox>>> calc_moves(const Position& pos) override;

private:
    bool first_move = true;
};

