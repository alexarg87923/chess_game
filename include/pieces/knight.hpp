#ifndef KNIGHT_H
#define KNIGHT_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "piece.hpp"

class Knight : public Piece {
public:
    Knight(char row, int col, Color team_color, sf::Vector2f size, Move_Handler& handler);
    Knight(const Position &pos, Color team_color, sf::Vector2f size, Move_Handler& handler);

    std::vector<Position> get_moves(const Position& pos) const override;
};

#endif
