#ifndef QUEEN_H
#define QUEEN_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "pieces/bishop.hpp"
#include "pieces/rook.hpp"

#include "board.hpp"


class Queen : public Rook, public Bishop {
public:
    Queen();
    ~Queen();

    Queen(char row, int col, char team_color);
    Queen(Position pos, char team_color);

    std::vector<Position> get_moves(Position pos, bool get_every_move) override;

    void calc_valid_moves() override;
private:
    std::string name = "queen"; 
};

#endif
