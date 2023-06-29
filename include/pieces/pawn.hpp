#ifndef PAWN_H
#define PAWN_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <piece.hpp>

#include "board.hpp"


class Pawn : public Piece {
public:
    Pawn();
    ~Pawn();
    Pawn(char row, int col, char team_color);
    Pawn(Position pos, char team_color);

    void update_position(Position pos) override;

    void calc_valid_moves() override;
private:
    bool first_move = true;
    std::string name = "pawn"; 
};

#endif
