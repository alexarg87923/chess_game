#ifndef KNIGHT_H
#define KNIGHT_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <piece.hpp>

#include "board.hpp"


class Knight : public Piece {
public:
    Knight();
    ~Knight();

    Knight(char row, int col, char team_color);
    Knight(Position pos, char team_color);

    void calc_valid_moves() override;
private:
    std::string name = "knight"; 
};

#endif
