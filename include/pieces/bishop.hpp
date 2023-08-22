#ifndef BISHOP_H
#define BISHOP_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "piece.hpp"

class Board;

class Bishop : virtual public Piece {
public:
    Bishop();
    ~Bishop();

    Bishop(char row, int col, Color team_color, sf::Vector2f size);
    Bishop(const Position& pos, Color team_color, sf::Vector2f size);

protected:
    virtual std::vector<Position> get_moves(const Position& pos) const override;
};

#endif
