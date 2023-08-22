#ifndef KNIGHT_H
#define KNIGHT_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "piece.hpp"

class Board;

class Knight : public Piece {
public:
    Knight();
    ~Knight();

    Knight(char row, int col, char team_color);
    Knight(Position pos, char team_color);

    std::vector<Position> get_moves(Position pos, bool get_every_move = false) override;

    void calc_valid_moves() override;
private:
    std::string name = "knight"; 
};

#endif
