#ifndef QUEEN_H
#define QUEEN_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "pieces/bishop.hpp"
#include "pieces/rook.hpp"

class Queen : public Rook, public Bishop {
public:
    Queen();
    ~Queen();

    Queen(char row, int col, Color team_color, sf::Vector2f size);
    Queen(const Position& pos, Color team_color, sf::Vector2f size);

    std::map<int, std::queue<Position>> calc_moves(const Position& pos) const override;
};

#endif
