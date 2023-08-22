#ifndef KNIGHT_H
#define KNIGHT_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "piece.hpp"

class Knight : public Piece {
public:
    Knight();
    ~Knight();

    Knight(char row, int col, Color team_color, sf::Vector2f size);
    Knight(const Position &pos, Color team_color, sf::Vector2f size);

    std::map<int, std::queue<Position>> calc_moves(const Position& pos) const override;
};

#endif
