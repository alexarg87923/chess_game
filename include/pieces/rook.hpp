#ifndef ROOK_H
#define ROOK_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "piece.hpp"

class Rook : virtual public Piece {
public:
    Rook(char row, int col, Color team_color, sf::Vector2f size, Move_Handler& handler);
    Rook(const Position& pos, Color team_color, sf::Vector2f size, Move_Handler& handler);

protected:
    virtual std::vector<Position> get_moves(const Position& pos, bool get_every_move = false) const override;
};

#endif
