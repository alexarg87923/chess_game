#ifndef PAWN_H
#define PAWN_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "piece.hpp"

class Pawn : public Piece {
public:
    Pawn(char row, int col, Color team_color, sf::Vector2f size, Move_Handler& handler);
    Pawn(const Position& pos, Color team_color, sf::Vector2f size, Move_Handler& handler);

    std::vector<Position> get_moves(const Position& pos) const override;

private:
    bool first_move = true;
};

#endif
