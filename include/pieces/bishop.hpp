#ifndef BISHOP_H
#define BISHOP_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "piece.hpp"

class Bishop : virtual public Piece {
public:
    Bishop(char row, int col, Color team_color, sf::Vector2f size, Move_Handler& handler);
    Bishop(const Position& pos, Color team_color, sf::Vector2f size, Move_Handler& handler);

protected:
    virtual std::vector<Position> get_moves(const Position& pos, bool get_every_move = false) const override;
};

#endif
