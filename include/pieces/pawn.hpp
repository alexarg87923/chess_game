#ifndef PAWN_H
#define PAWN_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "piece.hpp"

class Board;

class Pawn : public Piece {
public:
    Pawn();
    ~Pawn();
    Pawn(char row, int col, char team_color);
    Pawn(Position pos, char team_color);

    std::vector<Position> get_moves(Position pos, bool get_every_move = false) override;

    void update_position(Position pos) override;

    void calc_valid_moves() override;
private:
    bool first_move = true;
    std::string name = "pawn"; 
};

#endif
