#ifndef BISHOP_H
#define BISHOP_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <piece.hpp>

#include "board.hpp"


class Bishop : virtual public Piece {
public:
    Bishop();
    ~Bishop();

    Bishop(char row, int col, char team_color);
    Bishop(Position pos, char team_color);

    void calc_valid_moves() override;
protected:
    void calculate_bishop_path(Position pos);
private:
    std::string name = "bishop"; 

};

#endif
