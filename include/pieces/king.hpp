#ifndef KING_H
#define KING_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "piece.hpp"

class King : public Piece {
public:
    King();
    ~King();

    King(char row, int col, Color team_color, sf::Vector2f size);
    King(const Position& pos, Color team_color, sf::Vector2f size);

    std::map<int, std::queue<Position>> calc_moves(const Position& pos) const override;

private:
    bool already_moved = false;
};

#endif
