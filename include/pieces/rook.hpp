#ifndef ROOK_H
#define ROOK_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "piece.hpp"

#include "board.hpp"


class Rook : virtual public Piece {
public:
    Rook();
    ~Rook();

    Rook(char row, int col, char team_color);
    Rook(Position pos, char team_color);
    void calc_valid_moves() override;

protected:
    std::vector<Position> get_moves(Position pos, bool get_every_move = false) override;

private:
    std::string name = "rook"; 
};

#endif
